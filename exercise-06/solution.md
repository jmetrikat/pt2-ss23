## Aufgabe 3

Die Komplexität des Algorithmus ergibt sich aus den Schleifen und Funktionsaufrufen in der Datei `solver.cpp`: Zu Beginn wird `computeFinalRewards` aufgerufen, welche einmal über alle States läuft.

Es folgen vier verschachtelte Loops: In `compute_policy` wird für alle Zeitschritte, für alle States `computeExpectedRewardForTimeAndState` berechnet. Dort wird für alle Aktionen `computeExpectedRewardForAction` und dort schließlich für alle Ereignisse die `EventProbability` berechnet.

Kombiniert ergibt sich eine Komplexität von $O(T \cdot S \cdot A \cdot E  + S)$.
