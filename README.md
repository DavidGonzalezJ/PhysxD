# PhysxD
Proyeto hecho para la asignatura Simulación física para videojuegos de la UCM.

Proyecto consta de un sistema de partículas con escenas para la simulación de fuego, lluvia y nieve y fuentes. 
Clases referentes a la implementacion de Rigid Bodies que permiten aplicar fuerzas a un cuerpo en un punto determinado y con un torque concreto y que éste actúe en consecuencia.

También cuenta con un cargador de .obj para añadir a la escena diferentes objetos con malla.
Para la implementación del cargador nos hemos basado en el siguiente tutorial: 
http://www.opengl-tutorial.org/es/beginners-tutorials/tutorial-7-model-loading/

# Ejecución
Para ejecutar el proyecto descargar Master, compilar y ejecutar (Ctrl + F5).

# Código
El código consta de un Main donde podemos seleccionar la escena que se va a ejecutar. La escena final es el conjunto de todas donde podemos ver la simulación de un avión que se mueve en torno a una ecuación que describe un punto vinculado a una circunferencia generatríz.
Mediante derivadas conseguimos calcular la tangente a la curva y así calcular el giro del avión en los tres ejes (Yaw, Pitch y Roll).

El proyecto consta de una clase World, que aplica las fuerzas básicas como la gravedad. Para simular el paso utilizamos el método de Euler.

Tenemos clases genéricas para la gestión de objetos como "Objeto3D" donde se implementan los atributos genéricos de todos los objetos de la escena.
De ella heredan subclases como la clase "Malla" y "RigidBody". 
La clase que carga el .obj, lee el archivo y transforma la malla a un objeto de nuestra clase "Malla" para poder trabajar con él y realizarle transformaciones básicas como rotación, transalcion y escala.


