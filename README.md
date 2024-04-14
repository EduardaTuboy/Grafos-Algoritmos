# Grafos-Algoritmos

## Busca em Grafos
![image](https://github.com/EduardaTuboy/Grafos-Algoritmos/assets/128496419/22d571ba-3d42-435f-8abd-affd3b70df48)

*Fonte: ChatGPT*

**BFS:** Entra no último filho que ele mapeou

Em grafos não ponderados, a escolha entre a busca em largura (BFS) e a busca em profundidade (DFS) depende do objetivo específico da busca, pois ambos os algoritmos têm suas forças e casos de uso onde um pode ser mais adequado que o outro. Vamos considerar alguns cenários comuns:

### Encontrando o Caminho Mais Curto

- **BFS** é geralmente preferido para encontrar o caminho mais curto em grafos não ponderados porque ele explora todos os vértices a uma distância \(d\) antes de se mover para os vértices a uma distância \(d+1\). Isso garante que, assim que o destino for alcançado, o caminho encontrado será o mais curto possível em termos de número de arestas.
EX: De 0 até 3:
    BFS faz: 0, 1, 3
    DFS faz: 0, 1, 2, 3

### Explorando Grafos

- **DFS** pode ser mais útil em situações onde você precisa explorar o grafo o mais completamente possível a partir de um vértice de origem, seguindo um caminho até o final antes de retroceder. Por exemplo, o DFS é frequentemente usado em algoritmos de classificação topológica ou para encontrar componentes conectados em grafos não direcionados, bem como componentes fortemente conectados em grafos direcionados. Isso porque você segue caminhos acessíveis do grafo, e não pula partes do grafo como no BFS.

### Uso de Memória

- **DFS** tende a usar menos memória que o BFS porque o BFS precisa armazenar todos os vértices de uma determinada "fronteira" em memória ao mesmo tempo, o que pode ser significativo em grafos grandes e densos. O DFS, por outro lado, armazena apenas a pilha de chamadas recursivas correspondente ao caminho atual sendo explorado.

### Simplicidade e Implementação

- Em alguns casos, **DFS** pode ser considerado mais simples de implementar, especialmente de forma recursiva, enquanto o BFS geralmente requer a implementação de uma fila.

### Aplicações Específicas

- **BFS** é frequentemente utilizado em algoritmos que necessitam de nivelamento, como determinar o menor número de passos necessários para alcançar todos os pontos a partir de um ponto de origem, ou em algoritmos para determinar a conectividade em redes sociais, onde a distância entre os usuários (número de conexões) é relevante.
- **DFS** é comumente aplicado em problemas que envolvem a exploração de todas as combinações ou permutações possíveis dentro de um espaço de solução, como em problemas de backtracking e puzzles.

Portanto, em grafos não ponderados, a escolha entre BFS e DFS depende fortemente do problema específico e dos objetivos. Ambos têm seus méritos, e a seleção entre um e outro deve ser baseada na natureza da tarefa a ser realizada.

As complexidades de tempo e espaço dos algoritmos de busca em largura (BFS, do inglês "Breadth-First Search") e busca em profundidade (DFS, do inglês "Depth-First Search") são conceitos fundamentais para entender a eficiência desses algoritmos ao explorar grafos. Vamos detalhá-las considerando um grafo \(G\) com \(V\) vértices e \(E\) arestas.

### Complexidade de Tempo

- **BFS**: A complexidade de tempo do BFS é \(O(V + E)\) para grafos representados por listas de adjacência, que é o caso mais comum. O BFS visita cada vértice uma única vez, o que custa \(O(V)\), e também percorre todas as arestas nos grafos, o que custa \(O(E)\). Em grafos densos, onde \(E\) é próximo de \(V^2\), a complexidade pode ser vista como \(O(V^2)\) porque o número de arestas domina a expressão.

- **DFS**: Similarmente, a complexidade de tempo do DFS é \(O(V + E)\) quando o grafo é representado por listas de adjacência. O raciocínio é o mesmo que para o BFS: cada vértice é visitado uma vez, e o algoritmo percorre todas as arestas para explorar profundamente o grafo. Assim, o termo \(O(V + E)\) cobre tanto a visita aos vértices quanto a exploração das arestas. Em grafos densos, a complexidade também tende a \(O(V^2)\).

### Complexidade de Espaço

- **BFS**: A complexidade de espaço do BFS é \(O(V)\), pois, no pior caso, pode precisar armazenar todos os vértices em uma fila. Isso ocorre quando o grafo está em sua maior "largura", ou seja, quando um vértice está diretamente conectado a todos os outros vértices que ainda não foram visitados.

- **DFS**: A complexidade de espaço para o DFS, quando implementado de forma recursiva, é \(O(V)\) devido à pilha de chamadas de recursão. No pior caso, isso ocorre quando o grafo é implementado como uma "lista longa" de vértices, onde cada vértice está conectado apenas ao próximo vértice na lista (exceto o último vértice), fazendo com que a pilha de chamadas recursivas cresça linearmente com o número de vértices. Se o DFS for implementado de forma iterativa com uma pilha explícita, a análise de espaço permanece a mesma.

### Considerações

- A escolha entre BFS e DFS depende do problema específico que você está tentando resolver. Por exemplo, BFS é tipicamente usado para encontrar o caminho mais curto em grafos não ponderados, enquanto DFS pode ser útil para explorar todas as possíveis configurações em um espaço de problema ou para realizar uma ordenação topológica em grafos direcionados acíclicos.

- Para grafos representados por matrizes de adjacência, a complexidade de tempo tanto para BFS quanto para DFS pode ser vista como \(O(V^2)\), independentemente da densidade do grafo, devido à necessidade de examinar a matriz inteira.


