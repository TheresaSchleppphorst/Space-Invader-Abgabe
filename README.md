SPACE INVADERS
Das Spiel der pinken Aliens.

Als Erstes: Bauen und ausführen im JupyterHub: 

1. Ins Terminal navigieren, z. B. in der Konsole mit `cd cpp-sommersemester-2025/Abgabe_Vorlage`
2. Nur beim ersten Mal: Die Befehle `make getSFML` und `make getGTest` ausführen, um Ressourcen herunterzuladen.
3. Das Projekt und die Tests bauen: `make game` bzw. `make tests`
4. Den Pfad im Terminal anpassen: `export LD_LIBRARY_PATH=./SFML/lib:$LD_LIBRARY_PATH`
5. Das Spiel oder die Test ausführen (in der Konsolen-Anwendung, nicht VSCode!): `./game` oder `./tests`

Nun beginnt das Spiel!
Mit den Pfeiltasten (links und rechts) kannst Du das Raumschiff am unteren Bildschirmrand nach links und rechts verschieben. 
Mit der Leertaste kann das Raumschiffe Schüsse in Richtung der Aliens abfeuern. 
Ziel des Spiels ist es jedes Level alle Aliens zu treffen.
Die Aliens schießen zurück - ein Treffer bedeutet ein Lebensverlust. 
Die Powerups fallen gelegentlich runter - gute und schlechte, also pass auf, welche Du einfängst! Schlechte 
Powerups verlangsamen Deine Schussgeschwindigkeit, gute erhöhen sie.
Verloren hast Du, wenn Du alle drei Leben durch Treffer verloren hast oder die Aliens die Höhe des Raumschiffs erreichen - denn dann ist ein Abschießen nicht mehr möglich!
Hast Du das Level geschafft? YAAAAY! Drücke Enter und es geht mit drei Leben weiter. Aber Achtung, die Schüsse der Aliens kommen öfter und schneller. Und auch die Aliens selber erhöhen auf Dauer ihre Geschwindigkeit! 
Hast Du verloren? Tja, Game Over! Mit Enter kannst Du aber einfach wieder von vorne anfangen!

Viel Spaß!