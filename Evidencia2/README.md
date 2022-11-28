# Contexto del problema:
El programa debe:

1. leer un archivo de entrada que contiene la información de un grafo representado en forma de una matriz de adyacencias con grafos ponderados
El peso de cada arista es la distancia en kilómetros entre colonia y colonia, por donde es factible meter cableado.

El programa debe desplegar cuál es la forma óptima de cablear con fibra óptica conectando colonias de tal forma que se pueda compartir información entre cuales quiera dos colonias.

2. Debido a que las ciudades apenas están entrando al mundo tecnológico, se requiere que alguien visite cada colonia para ir a dejar estados de cuenta físicos, publicidad, avisos y notificaciones impresos. por eso se quiere saber ¿cuál es la ruta más corta posible que visita cada colonia exactamente una vez y al finalizar regresa a la colonia origen?
El programa debe desplegar la ruta a considerar, tomando en cuenta que la primera ciudad se le llamará A, a la segunda B, y así sucesivamente

3. El programa también debe leer otra matriz cuadrada de N x N datos que representen la capacidad máxima de transmisión de datos entre la colonia i y la colonia j. Como estamos trabajando con ciudades con una gran cantidad de campos electromagnéticos, que pueden generar interferencia, ya se hicieron estimaciones que están reflejadas en esta matriz.

La empresa quiere conocer el flujo máximo de información del nodo inicial al nodo final. Esto debe desplegarse también en la salida estándar.

Por último

4. Teniendo en cuenta la ubicación geográfica de varias "centrales" a las que se pueden conectar nuevas casas, generar un polígono que marque la zona que se encuentre delimitada por dichas centrales

Entrada:
Un numero entero N que representa el número de colonias en la ciudad
matriz cuadrada de N x N que representa el grafo con las distancias en kilómetros entre las colonias de la ciudad
matriz cuadrada de N x N que representa las capacidades máximas de flujo de datos entre colonia i y colonia j
lista de N pares ordenados de la forma (A,B) que representan la ubicación en un plano coordenado de las centrales

Salida:
1. Forma de cablear las colonias con fibra
(lista de arcos de la forma (A,B))
2. ruta a seguir por el personal que reparte correspondencia, considerando inicio y fin en al misma colonia.
3. valor de flujo máximo de información del nodo inicial al nodo final
4. lista de puntos en orden contrario a las manecillas del reloj que delimitan la zona

 # Casos de prueba:  
 
 > **Nota:** El programa toma en cuenta únicamente entradas válidas, no está diseñado para encontrar errores en el input. Los casos de prueba están basados en grafos completos a indicaciones del profesor y están diseñados para llevar a los algoritmos utilizados al límite para comprobar su funcionalidad con ejemplos de matrices pequeñas; sin embargo se pudieran probar también matrices de mayor tamaño tanto como en número de vértices como en el peso de las aristas.


 **Caso 1:**
Para probar el primer algoritmo se tiene un caso de prueba donde las ciudades son equidistantes. El algoritmo en este caso toma 

Ejemplo
4
0 1 1 1 
1 0 1 1
1 1 0 1
1 1 1 0


**Caso 2:**
Este caso de prueba tiene el mismo concepto que el anterior, sólo que se le modificó el número de nodos para aumentar los datos ingresados.
Al momento de ser aplicado al segundo algoritmo tiene una interpretación muy diferente. Al ser el  un algoritmo de tipo greedy, debería de arrojar la primera solución que encuentre, en este caso, sería unir los puntos por orden de aparición.

Ejemplo:
6
0 1 1 1 1 1
1 0 1 1 1 1
1 1 0 1 1 1
1 1 1 0 1 1
1 1 1 1 0 1
1 1 1 1 1 0

 **Caso 3:**
Se le agregan más nodos al grafo, generando asi más información que procesar. 

10
0 132 102 433 98 23 484 223 67 228
108 0 337 18 97 31 398 88 385 185
82 285 0 307 178 489 244 238 434 64
215 306 131 0 395 229 82 10 214 324
393 454 139 102 0 112 202 115 224 53
333 321 149 174 332 0 431 260 130 200
493 336 22 89 368 432 0 316 24 145
334 195 417 125 256 230 303 0 180 176
412 344 468 62 332 312 198 236 0 421
92 408 142 269 118 240 415 145 285 0
 
 **Caso 4:**
 Para poner a prueba el último punto, se utilizó una lista de 150 puntos en un plano para probar el algoritmo de convex Hull con una gran cantidad de datos. Dichos puntos fueron generados mediante un programa en python.

 Ejemplo:
(417,304)
(663,580)
(695,188)
(734,719)
(192,13)
(69,513)
(343,209)
(320,477)
(732,469)
(534,29)
(307,572)
(220,564)
(493,662)
(20,511)
(127,442)
(566,428)
(629,125)
(609,488)
(290,644)
(579,384)
(114,690)
(19,433)
(539,15)
(571,89)
(217,352)
(189,19)
(669,495)
(542,684)
(432,530)
(281,636)
(99,262)
(95,202)
(740,105)
(683,489)
(192,775)
(795,570)
(727,463)
(245,412)
(653,732)
(270,364)
(568,663)
(231,283)
(120,252)
(689,648)
(624,680)
(777,44)
(288,691)
(524,289)
(201,543)
(502,282)
(460,750)
(457,187)
(297,69)
(489,277)
(85,375)
(287,225)
(678,765)
(352,6)
(73,615)
(570,22)
(302,515)
(623,281)
(188,299)
(722,709)
(749,284)
(733,24)
(771,732)
(692,377)
(439,308)
(510,618)
(586,785)
(644,349)
(97,319)
(356,419)
(364,397)
(435,634)
(459,493)
(50,659)
(715,170)
(20,186)
(50,413)
(768,407)
(579,90)
(620,606)
(648,373)
(553,591)
(438,699)
(428,582)
(749,101)
(470,754)
(127,254)
(564,426)
(103,674)
(230,758)
(260,150)
(460,177)
(17,586)
(15,531)
(603,279)
(657,582)
(728,572)
(398,309)
(333,63)
(668,633)
(612,587)
(5,391)
(36,415)
(335,64)
(35,228)
(631,508)
(217,479)
(0,205)
(555,99)
(768,714)
(289,525)
(143,510)
(364,193)
(789,601)
(591,228)
(604,770)
(105,161)
(35,380)
(150,62)
(232,449)
(535,444)
(505,20)
(693,755)
(373,716)
(503,24)
(212,700)
(714,204)
(470,772)
(226,562)
(336,543)
(117,676)
(141,545)
(627,654)
(357,608)
(305,632)
(598,631)
(93,608)
(437,741)
(218,789)
(103,678)
(174,663)
(396,782)
(262,76)
(189,319)
(187,487)
(69,146)