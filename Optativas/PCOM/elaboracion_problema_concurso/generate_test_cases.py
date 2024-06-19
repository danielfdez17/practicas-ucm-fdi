import random

MAX_N = 100

def generar_caso_aleatorio(n):
    return [random.randint(-MAX_N, MAX_N) for _ in range(n)]

def generar_caso_limite():
    return [random.randint(-MAX_N, MAX_N) for _ in range(MAX_N)]

def guardar_caso(caso, file):
    file.write(f"{len(caso)}\n")
    file.write(" ".join(map(str, caso)) + "\n")

# Generar casos de prueba
casos = [
    *(generar_caso_aleatorio(i) for i in range(1, MAX_N)),
    *(generar_caso_limite() for i in range(1, MAX_N)),
    # generar_caso_aleatorio(1), 
    # generar_caso_aleatorio(2),
    # generar_caso_aleatorio(3),
    # generar_caso_aleatorio(4),
    # generar_caso_aleatorio(5),
    # generar_caso_aleatorio(6),
    # generar_caso_aleatorio(7),
    # generar_caso_aleatorio(8),
    # generar_caso_aleatorio(9),
    # generar_caso_aleatorio(10),
    # generar_caso_aleatorio(11),  
    # generar_caso_aleatorio(12),  
    # generar_caso_aleatorio(13),  
    # generar_caso_aleatorio(14),  
    # generar_caso_aleatorio(15),  
    # generar_caso_aleatorio(16),  
    # generar_caso_aleatorio(17),  
    # generar_caso_aleatorio(18),  
    # generar_caso_aleatorio(19),  
    # generar_caso_aleatorio(20),  
    # generar_caso_aleatorio(30),  
    # generar_caso_aleatorio(40),  
    # generar_caso_aleatorio(50),
    # generar_caso_aleatorio(60),
    # generar_caso_aleatorio(70),
    # generar_caso_aleatorio(80),
    # generar_caso_aleatorio(90),
    # generar_caso_aleatorio(100),
    # generar_caso_aleatorio(200),
    # generar_caso_aleatorio(300),
    # generar_caso_aleatorio(400),
    # generar_caso_aleatorio(500),
    # generar_caso_aleatorio(600),
    # generar_caso_aleatorio(700),
    # generar_caso_aleatorio(800),
    # generar_caso_aleatorio(900),
    # generar_caso_aleatorio(1000),
    # generar_caso_aleatorio(2000),
    # generar_caso_aleatorio(3000),
    # generar_caso_aleatorio(4000),
    # generar_caso_aleatorio(5000),
    # generar_caso_aleatorio(6000),
    # generar_caso_aleatorio(7000),
    # generar_caso_aleatorio(8000),
    # generar_caso_aleatorio(9000),
    # generar_caso_aleatorio(MAX_N),  
    # generar_caso_limite(MAX_N, 1),
    # generar_caso_limite(MAX_N, -1), 
]

# Guardar casos de prueba en un archivo
with open("elaboracion_problema_concurso/extended_input.txt", "w") as file:
    for caso in casos:
        guardar_caso(caso, file)
