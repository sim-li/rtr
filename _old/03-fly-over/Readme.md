# Aufgabe 3: Fly Over

## Aufgabe 3.1
Mit Hilfe von CrazyBump wurde von einer gegebenen Textur eine NZ-Map erstellt, also eine Karte die Normalen- sowieo Höheninformationen enthält.
Per Displacement Mapping wurde aus einer Ebene das Terrain erstellt. Abhänhig von der Höhe der Vertices wurden verschiedene Texturen auf das Terrain gemappt die in einem kleinen Bereich mit angrenzenden Texturen interpoliert werden. 
Die Stellen, die mit der Wassertextur versehen wurden, besitzen eine höhere "Shininess" als der Rest. Außerdem wurde diese Textur durch Übergabe der vergangenen Zeit animiert.

## Aufgabe 3.2
Die Steuerung der Kamera sowie der anderen "Flugzeuge" (Kugeln) wurde durch Verwendung der Klasse "SimpleWasd" realisiert. Die Steuerung der Kamera ist dadurch über W, A, S, D, E, Q (Translation) sowie Up, Down, Left, Right (Rotation) möglich.
Eine Erhöhung der Geschwindigkeit kann durch Gedrückthalten von "W" erreicht werden. Abbremsen ist durch Antippen von "S" möglich. 

## Aufgabe 3.3
Initial wird unser Terrain (also die Ebene) 9 mal platziert und ergeben dadurch eine 3x3-Matrix deren Mittelpunkt im Mittelpunkt des Weltkoordinatensystem liegt.
Die Kamera erhält initial ebenfalls diese Position. Bewegt sich die Kamera (unser Flugzeug) nun beispielsweise in negativer Z-Richtung und überschreitet dabei den Übergang zur nächsten Ebene, wird die 3er-Reihe von Ebenen deren Z-Positionskoordinate am größten ist, per Translation verschoben, sodass diese 3 Ebenen danach von allen 9 Ebenen den kleinsten Z-Wert haben.
Die 3 Ebenen die also am weitesten vom Sichtfeld der kamera entfernt sind (also optisch hinter dem Flugzeug nicht sichtbar sind), werden in Blickrichtung der Kamera um "Länge der Ebene" * 3 verschoben.
Hierdurch wird der Effekt der "endlosen Landschaft" erzeugt, wobei initial nur 9 Ebenen erzeugt werden, die zur Laufzeit lediglich verschoben werden.

## Aufgabe 3.4
Per Cube Mapping wurde eine Skybox erstellt.

## Aufgabe 3.5
Nach Recherchen wurde zunächst der Nebeleffekt im Fragmentshader des Terrains implementiert (Quellen sind im Quellcode angegeben). Hierzu musste die im Vertextshader berechnete Position des aktuellen Vertices an den Fragmentshader übergeben werden, der dann abhängig von der aktuellen Entfernung der Kamera zum jeweiligen Vertext die Nebelintensität berechnet und auf dem Terrain darstellt.
Nachfolgend wurde der Nebeleffekt in Bodennähe mit Photoshop zur Skybox hinzugefügt.
Die Sichtweite der Kamera (Beginn des dichten Nebels) wurde hierbei so justiert, dass zumindest bei relativ geringer Flughöhe das "Aufploppen" der Ebenen in Blickrichtung nicht sichtbar ist.

## Zusatz
Um die Kamera herum werden 50 Kugeln an zufälliger Position mit zufälliger Farbe erzeugt, die andere Flugzeuge darstellen sollen (Animation durch Rotation und Translation).