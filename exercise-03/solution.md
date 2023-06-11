# Lösung für Aufgabe 3 & 4

## Ausgabe
**Comparing worst cases**

Worst-Case Bubble Sort - Reverse Sorted: 10 9 8 7 6 5 4 3 2 1
- BS, n=10, counts= 45
- BS, n=100, counts= 4950
- BS, n=1000, counts= 499500

Worst-Case Quick Sort - Pivot is smallest element: 0 1 2 3 4 5 6 7 8 9
- QS, n=10, counts= 54
- QS, n=100, counts= 5049
- QS, n=1000, counts= 500499

Worst-Case Merge Sort - Reversed Logic: 7 3 5 9 1 6 2 4 8 0
- MS, n=10, counts= 34
- MS, n=100, counts= 640
- MS, n=1000, counts= 9624

**Comparing best cases**

Best-Case Bubble Sort - Already Sorted: 0 1 2 3 4 5 6 7 8 9
- BS, n=10, counts= 9
- BS, n=100, counts= 99
- BS, n=1000, counts= 999

Best-Case Quick Sort - Pivot is middle element: 4 0 2 3 1 7 5 6 8 9
- QS, n=10, counts= 24
- QS, n=100, counts= 607
- QS, n=1000, counts= 11171

Best-Case Merge Sort - Already Sorted: 0 1 2 3 4 5 6 7 8 9
- MS, n=10, counts= 9
- MS, n=100, counts= 99
- MS, n=1000, counts= 999

## Diskussion
**Bubble Sort**

Die Anzahl der Vergleiche für den Worst Case für den entspricht unseren Erwartungen, da eine Laufzeit von $O(n^2)$ erzielt wird. Genau genommen überspringen wir die bereits sortierten Elemente am Ende des Arrays, sodass sich $\frac{n^2 +n} 2$ Vergleiche ergeben. Dies ist der gewünschte Effekt für ein umgekehrt sortiertes Array.

Auch der Best Case für den Bubble Sort trifft unsere Erwartung mit einer Laufzeit von $O(n)$, da das Array bereits sortiert ist und somit nur $n-1$ Vergleiche benötigt werden.

**Quick Sort**

Die Anzahl der Vergleiche für den Worst Case für den entspricht unseren Erwartungen, weil eine Laufzeit von $O(n^2)$ erzielt wird. Dies ergibt sich, da das Pivot Element immer das kleinste Element ist und daher statt zwei gleichgroßen Teilarrays ein Array der Größe 1 und ein Array der Größe $n-1$ entsteht. Anstatt also jedes Mal die Größe des Arrays zu halbieren, benötigen wir eine Rekurssionstiefe von $n$, um das Array vollständig zu bearbeiten. Schlechter kann die Laufzeit nicht sein und befindet sich somit in ähnlicher Größenordnung wie der Worst Case für Bubble Sort.

Für den Best Case befinden wir uns in der Größenordnung von $O(n \cdot log(n))$, da wir das Array immer in zwei gleichgroße Teilarrays aufteilen. Dies ist der Fall, weil wir die Pivot Elemente immer perfekt mittig wählen. Die Rekusrsionstiefe beträgt somit bloß $log (n)$.

**Merge Sort**

Mit unserer speziellen reverse Implementierung für den Worst Case benötigen wir ziemlich genau $n \cdot log(n)$ Vergleiche. Dies entspricht unserer Erwartung, da eine schlechtere Laufzeit für Merge Sort nicht möglich ist. Wir benötigen eine Rekursionstiefe von $log(n)$ und müssen in jedem Schritt $n$ Elemente vergleichen.

Auch der Best Case für den Merge Sort trifft unsere Erwartung mit einer Laufzeit von O(n), da das Array bereits sortiert ist und somit gemäß unserer Implementierung frühzeitig abgebrochen wird. Wir benötigen somit bloß $n-1$ Vergleiche.

**Abschließende Gedanken**

Es stellt sich die Frage, ob die Anzahl der Vergleiche überhaupt ein praktisch sinnvoller Indikator für die Laufzeit ist.

Mit Sicherheit spielt die Anzahl an Vergleichen eine wichtige Rolle, sollte allerdings nicht als alleiniger Indikator für die Laufzeit verwendet werden. Sie ist einer von mehreren Anhaltspunkten, aber auch Faktoren wie der Speicherbedarf sind in der Praxis von Bedeutung. So ist möglicherweise ein zugriffs- und speicherminimaler Algorithmus mit einer höheren Anzahl an Vergleichen schneller als ein Algorithmus mit weniger Vergleichen, der dafür aber mehr Speicher benötigt.

Außerdem relevant ist die Art des Inputs, wenn es um die Wahl des schnellsten Algorithmus geht. In der Praxis kann es daher sinnvoll sein, für die gegebene Anforderungen den vorteilhafesten Algorithmus zu wählen und anzupassen.
