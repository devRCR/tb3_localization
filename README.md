# tb3_localization

Actividad 1 del CURSO DE CAPACITACIÓN EN NAVEGACIÓN AUTÓNOMA DE ROBOTS MÓVILES

Para esta actividad se trabajará con el robot turtlebot3, con el modelo de robot que usted prefiera, la simulación se debe realizar en el mundo turtlebot3_house. Para realizar la actividad, debe seguir los siguientes pasos:

Debe crear un paquete llamado tb3_localization.

Realizar el mapeo con el paquete de gmapping, como se indica en el siguiente link. https://emanual.robotis.com/docs/en/platform/turtlebot3/slam/

Crear un nodo que publique la localización inicial del robot, en el mapa, 5 veces durante sólo un segundo. Una vez pasado ese segundo, el nodo debe dejar de publicar información o cerrarse.

Necesitamos indicar la posición del robot en el mapa, por tanto con un nodo indicamos la posición, orientación y covarianza (copiar de los valores de turtlebot3 cuando inicia su localización) iniciales apropiadas para el robot, como si lo hiciera el botón 2D pose estimate, pero desde un nodo.

Una vez ubicado, el robot sigue sin tener la certidumbre adecuada para saber donde está, por tanto, se debe mejorar la certidumbre de la localización del robot haciendo que este gire un poco y luego vuelva a su estado inicial. Cree un nodo que controle el movimiento angular del robot, este proceso debe durar menos de 8 segundos.
