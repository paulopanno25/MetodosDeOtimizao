import time
import random
from itertools import product
from mip import Model, xsum, BINARY
from plotly.subplots import make_subplots
import numpy as np

import plotly.io as pio
pio.renderers.default='browser'

instancia = 'j10.sm'
#instancia = 'j301_1.sm'
#instancia = 'j12060_7.sm'
arq_solucao = 'j10.sol'
#---
metodo = 3                 # 0: resolver de forma exata (biblioteca MIP); 1: ler solução do arquivo; 2: construtiva; 3: construtiva com ajuste de horário
mostrar_violacoes = False  # mostrar as violações no cálculo da FO (caso existam)


#-----------------------------------------------------------------------------------------------------------------------
def ler_instancia(instancia):
    with open(instancia) as f:
        arq = f.readlines()
    #---
    recursos = arq[8]
    recursos = recursos.split()
    recursos = recursos[3]
    recursos = int(recursos)
    #---
    tarefas = arq[14]
    tarefas = tarefas.split()
    tarefas = tarefas[1]
    tarefas = int(tarefas)
    #---
    precedencias = []
    mat_sucessores = [[0] * (tarefas+2) for i in range(tarefas+2)]
    for i in range(tarefas+2):
        aux = arq[18+i]
        aux = aux.split()
        for j in range(int(aux[2])):
            precedencias.append([int(i), int(aux[3+j])-1])
            mat_sucessores[int(i)][int(aux[3+j])-1] = 1
    #---
    duracao = []
    consumo_recursos = []
    for i in range(tarefas+2):
        aux = arq[i+24+tarefas].split()
        duracao.append(int(aux[2]))
        aux2 = []
        for j in range(recursos):
            aux2.append(int(aux[3+j]))
        consumo_recursos.append(aux2)
    #---
    recursos_disponiveis = []
    aux = arq[-2]
    aux = aux.split()
    for i in range(recursos):
        recursos_disponiveis.append(int(aux[i]))
    return tarefas, recursos, precedencias, duracao, consumo_recursos, recursos_disponiveis, mat_sucessores
#-----------------------------------------------------------------------------------------------------------------------

#-----------------------------------------------------------------------------------------------------------------------
def ler_solucao(arq_sol, tarefas):
    with open(arq_sol) as f:
        arq = f.readlines()
    #---
    fo = arq[0]
    fo = fo.split()
    fo = fo[1]
    #---
    makespan = arq[1]
    makespan = makespan.split()
    makespan = makespan[1]
    #---
    solucao = []
    for i in range(tarefas+2):
        aux = arq[i+4].split()
        solucao.append([i+1, int(aux[1])])
    return makespan, fo, solucao
#-----------------------------------------------------------------------------------------------------------------------

#-----------------------------------------------------------------------------------------------------------------------
def resolver_problema(n, p, u, c, S):
    print('\nAguarde...')
    tempo_ini = time.time()
    (R, J, T) = (range(len(c)), range(len(p)), range(sum(p)))
    modelo = Model()
    x = [[modelo.add_var(name="x({},{})".format(j, t), var_type=BINARY) for t in T] for j in J]
    modelo.objective = xsum(t * x[n + 1][t] for t in T)
    for j in J:
        modelo += xsum(x[j][t] for t in T) == 1
    for (r, t) in product(R, T):
        modelo += (xsum(u[j][r] * x[j][t2] for j in J for t2 in range(max(0, t - p[j] + 1), t + 1)) <= c[r])
    for (j, s) in S:
        modelo += xsum(t * x[s][t] - t * x[j][t] for t in T) >= p[j]
    modelo.verbose = 0
    modelo.optimize()
    tempo_fim = time.time()
    solucao = []
    for (j, t) in product(J, T):
        if x[j][t].x >= 0.99:
            solucao.append([j + 1, t])
    return modelo.objective_value, tempo_fim - tempo_ini, solucao
#-----------------------------------------------------------------------------------------------------------------------

#-----------------------------------------------------------------------------------------------------------------------
def calcular_FO(solucao, tarefas, recursos, duracao, consumo_recursos, recursos_disponiveis, mat_sucessores, mostrar):
    if mostrar:
        print('\n\n----------------------------')
        print('CALCULO DA FO')
        print('----------------------------')

    #--- makespan
    makespan = 0
    for i in range(tarefas+2):
        id = solucao[i][0]-1
        x = solucao[i][1]
        makespan = max(makespan, x+duracao[id])
        
    #--- violacoes de precedencia
    vio_pre = 0 
    if mostrar:
        print('\nVIOLACOES DE PRECEDENCIA')
    for i in range(tarefas+2):
        id_1 = solucao[i][0]-1
        x_ini = solucao[i][1]
        x_fin = x_ini + duracao[id_1]
        for j in range(tarefas+2):
            if j != i:
                id_2 = solucao[j][0]-1
                if  mat_sucessores[id_1][id_2] == 1 and solucao[j][1] < x_fin:
                    vio_pre += x_fin - solucao[j][1]
                    if mostrar:
                        print(f'{id_1+1} {id_2+1} - Termino: {x_fin} - Inicio: {solucao[j][1]}')
                
    #--- violacoes de recursos
    duracao_total = sum(duracao)
    mat_consumo = [[0] * duracao_total for i in range(recursos)]
    for i in range(tarefas+2):
        id = solucao[i][0]-1
        x_ini = solucao[i][1]
        x_fin = x_ini + duracao[id]    
        for r in range(recursos):
            if consumo_recursos[id][r] != 0:
                for t in range(x_ini, x_fin, 1):
                    mat_consumo[r][t] += consumo_recursos[id][r]
    if mostrar:
        print('\nMATRIZ DE CONSUMO')
        for i in range(recursos):
            print(f'R{i+1}: {mat_consumo[i]}')
        print('\nVIOLACOES DE RECURSO')

    vio_rec = 0    
    for r in range(recursos):
        vet_vio = [max(0, mat_consumo[r][i] - recursos_disponiveis[r]) for i in range(duracao_total)]
        vio_rec += sum(vet_vio)
        if mostrar:
            print(f'R{r+1}:', vet_vio)
    
    #--- FO    
    fo = makespan + 10 * vio_pre + 10 * vio_rec;
   
    return makespan, vio_pre, vio_rec, fo
#----------------------------------------------------------------------------------------------------------------------- 

#-----------------------------------------------------------------------------------------------------------------------
def construtiva(tarefas, duracao, mat_sucessores):
    #---
    # matriz com o id das tarefas e a qtde de predecessores 
    soma = np.sum(mat_sucessores, axis=0)
    vet_pred = []
    for i in range(1, tarefas+1, 1):
        vet_pred.append([i, soma[i]])
    vet_pred.sort(key=lambda x: int(x[1]))
    #---
    # vetor binário indicando se uma tarefa foi inserida na solução ou não
    inseridos = [0] * (tarefas+2)
    inseridos[0] = 1
    inseridos[tarefas+1] = 1
    inseridos = [0] * (tarefas+2)
    inseridos[0] = 1
    #---
    # inserir a primeira tarefa (fictícia)
    solucao = []
    solucao.append([1,0])
    #--- 
    # lista com as tarefas ainda não inseridas na solução
    lista = [vet_pred[i-1][0] for i in range(1, tarefas+1, 1)]
    # inserir as tarefas restantes, desde que todos os predecessores já estejam na solução
    pos = 0
    while len(lista) > 0:
        id = lista[pos]
        pode = 1
        for j in range(tarefas+2):
            if mat_sucessores[j][id] == 1 and inseridos[j] == 0:
                pode = 0
                break
        if pode == 1:
            solucao.append([id+1,0])
            inseridos[id] = 1
            lista.remove(id)
        else:
            pos += 1
            if pos == len(lista):
                pos = 0
    #---
    # inserir a última tarefa (fictícia)
    inseridos[tarefas+1] = 1
    solucao.append([tarefas+2,0])
    #---
    # definir o horário de início de cada tarefa de forma sequencial
    for i in range(1, tarefas+2, 1):
        id = solucao[i-1][0]
        solucao[i][1] = solucao[i-1][1] + duracao[id-1]    
        
    return solucao[tarefas+1][1], solucao
#-----------------------------------------------------------------------------------------------------------------------

#-----------------------------------------------------------------------------------------------------------------------
def ajustar_horarios(solucao, tarefas, recursos, duracao, consumo_recursos, recursos_disponiveis, mat_sucessores):
    #---
    # definir a matriz de consumo para todo o "intervalo" de tempo
    duracao_total = sum(duracao)
    mat_consumo = [[0] * duracao_total for i in range(recursos)]
    #---
    # definir o horário de término de cada tarefa
    hor_termino = [0] * (tarefas+2)
    for i in range(tarefas+1):
        id = solucao[i][0] - 1
        hor_termino[id] = solucao[i][1] + duracao[id] 
    #---
    # ajustar os horários para cada tarefa, seguindo a ordem na solução
    for i in range(1, tarefas+1, 1):
        id1 = solucao[i][0]-1
        #---
        # definir o menor horário mínimo possível para início da tarefa com base nos seus predecessores
        hor_ini = 0
        for j in range(tarefas+2):
            id2 = solucao[j][0]-1
            if mat_sucessores[id2][id1] == 1:
                hor_ini = max(hor_ini, hor_termino[id2])
        #---
        # incrementa o horário de início caso não haja algum recurso disponível para a tarefa
        sem_recurso = 1
        while sem_recurso == 1:
            sem_recurso = 0
            for r in range(recursos):
                if consumo_recursos[id1][r] != 0: 
                    flag = 1
                    for t in range(hor_ini, hor_ini+duracao[id1], 1):
                        if mat_consumo[r][t] + consumo_recursos[id1][r] > recursos_disponiveis[r]:                
                            flag = 0
                            break
                    if flag == 0:
                        hor_ini += 1
                        sem_recurso = 1
                        break
        #---
        # define os horário de início e término da tarefa
        solucao[i][1] = hor_ini
        hor_termino[id1] = solucao[i][1] + duracao[id1]
        #---
        # atualiza a matriz de consumo
        for r in range(recursos):
            if consumo_recursos[id1][r] != 0:
                for t in range(solucao[i][1], hor_termino[id1], 1):
                    mat_consumo[r][t] += consumo_recursos[id1][r]
    #---
    # define o horário de início da última tarefa (makespan)
    solucao[tarefas+1][1] = max(hor_termino)
    
    return solucao[tarefas+1][1], solucao   
#-----------------------------------------------------------------------------------------------------------------------

#-----------------------------------------------------------------------------------------------------------------------
# PROGRAMA PRINCIPAL
tarefas, recursos, precedencias, duracao, consumo_recursos, recursos_disponiveis, mat_sucessores = ler_instancia(instancia)
print('\n----------------------------')
print('INSTÂNCIA')
print('----------------------------')
print(f'Tarefas............: {tarefas}')
print(f'Recursos...........: {recursos}')
print(f'Precedencias.......: {precedencias}')
print(f'Duração............: {duracao}')
print(f'Consumo............: {consumo_recursos}')
print(f'Rec. disponíveis...: {recursos_disponiveis}')
print('Matriz de sucessores:')
for i in range(tarefas+2):
    print(f'{mat_sucessores[i]}  ')
#---
if metodo == 0:
     makespan, tempo, solucao = resolver_problema(tarefas, duracao, consumo_recursos, recursos_disponiveis, precedencias)
     fo = makespan
     print('\n\n----------------------------')
     print('SOLUÇÃO MIP')
elif metodo == 1:
     makespan, fo, solucao = ler_solucao(arq_solucao, tarefas)
     tempo = 0
     print('\n\n----------------------------')
     print('SOLUÇÃO ARQUIVO')
elif metodo == 2:
     print('\nAguarde...')
     tempo = time.time() 
     makespan, solucao = construtiva(tarefas, duracao, mat_sucessores)
     fo = makespan
     tempo = time.time() - tempo
     print('\n----------------------------')
     print('SOLUÇÃO CONSTRUTIVA')
else:
     print('\nAguarde...')
     tempo = time.time() 
     makespan, solucao = construtiva(tarefas, duracao, mat_sucessores)
     makespan, solucao = ajustar_horarios(solucao, tarefas, recursos, duracao, consumo_recursos, recursos_disponiveis, mat_sucessores)
     fo = makespan
     tempo = time.time() - tempo
     print('\n----------------------------')
     print('SOLUÇÃO CONSTRUTIVA AJUSTADA')     
print('----------------------------')
print(f'FO.........................: {fo}')
print(f'Makespan...................: {makespan}')
print(f'Tempo de execução (seg)....: {tempo:.2f}')
print(f'Solucao ([id, inicio]).....: {solucao}')
#---
# Calcular a FO
m, vp, vr, f = calcular_FO(solucao, tarefas, recursos, duracao, consumo_recursos, recursos_disponiveis, mat_sucessores, mostrar_violacoes)
print('\n\n----------------------------')
print('CALCULO DA FO')
print('----------------------------')
print(f'FO.........................: {f}')
print(f'Makespan...................: {m}')
print(f'Vio. precedencia...........: {vp}')
print(f'Vio. recursos..............: {vr}')
#---
# Criar o gráfico com a solução
solucao.sort(key=lambda x: int(x[1]))
print('\n\n----------------------------')
print('SOLUÇÃO ORDENADA PELO INICIO')
print('----------------------------')
print(solucao)
cores = []
for j in range(tarefas+2):
    cores.append("#"+''.join([random.choice('0123456789ABCDEF') for i in range(6)]))
fig = make_subplots(rows=recursos, cols=1, shared_xaxes=True, vertical_spacing=0.1, x_title='Unidades de tempo')
x_fin = [0] * recursos
y_fin = [0] * recursos
for i in range(tarefas+2):
    id = solucao[i][0]-1
    x = solucao[i][1]
    for j in range(recursos):
        if consumo_recursos[id][j] != 0:
            if x < x_fin[j]:
                y = y_fin[j]
            else:
                y = 0
            fig.add_scatter(x=[x, x, x+duracao[id], x+duracao[id]],
                            y=[y, y+consumo_recursos[id][j], y+consumo_recursos[id][j], y], fill='toself',
                            fillcolor=cores[i], opacity=1, name=f'Tarefa {id+1}<br>Início: {x}<br>Duração: {duracao[id]}<br>Consumo: {consumo_recursos[id][j]}', line=dict(color=cores[i], width=1),
                            marker=dict(size=1, line=dict(width=0, color=cores[i])), row=j+1, col=1)
            x_fin[j] = x+duracao[id]
            y_fin[j] = y+consumo_recursos[id][j]
fig.update_layout(title=f'Tarefas: {tarefas};   Recursos: {recursos};   Makespan: {makespan}')
for i in range(recursos):
    fig.update_yaxes(title_text=f'Recurso {i+1}<br>({recursos_disponiveis[i]})', row=i+1, col=1)
fig.update_layout(showlegend=False, template='plotly_dark')
fig.show()