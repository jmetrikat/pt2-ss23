[![Review Assignment Due Date](https://classroom.github.com/assets/deadline-readme-button-24ddc0f5d75046c5622901739e7c5dd533143b0c8e959d652212380cedb1ea36.svg)](https://classroom.github.com/a/oNCssGEh)
[![Open in Codespaces](https://classroom.github.com/assets/launch-codespace-7f7980b617ed060a017424585567c406b6ee15c891e84e1186181d67ecf80aa0.svg)](https://classroom.github.com/open-in-codespaces?assignment_repo_id=10969406)

# Programmiertechnik II SS23, Übung 1

Pro Übung gibt es 10 Punkte. Für die Zulassung zur Prüfung müssen in allen Übungen mindestens 50% der Punkte erzielt werden.

Der Code für diese Aufgabe kann sehr einfach im Github Codespace bearbeitet werden. Alternativ können Sie das Repository klonen und lokal bauen, make tests, ausgeführt im .vscode-Ordner, führt dann die Tests aus.

## Aufgabe 1 - GradingTable (6 Punkte)

Die folgende Übung dient als Einführung in C++ und das Abgabesystem.
Als Grundlage dient die letzte Übung aus PT1 im WS22/23.
Das in dieser Übung implementierte System zur Auswertung von Aufgaben soll in C++ mit einigen der nun verfügbaren Spracherweitungen erneut implementiert werden.
Dazu ist in diesem Repository ein Rahmen für alle notwendigen Komponenten gegeben.

Das System soll aus 2 Komponenten bestehen: Der GradingTable, die zuständig ist für das Einlesen der Datenbank aus der Datei grading_results.db, und den GradingAgents, die unterschiedliche Aufgaben zur Auswertung übernehmen sollen.

Die GradingTable soll eine einfach verkettete Liste speichern, die alle Einträge des .db-Files enthält. Dazu ist das aus PT1 bekannte Struct bereits gegebeben. GradingTable soll sowohl den Verweis auf das erste als auch auf das letzte Element dieser Liste speichern. Der Konstruktor der GradingTable bekommt eine Referenz auf einene C++-Filestream übergeben, der ausgelesen werden und in eine Liste umgewandelt werden soll. Die zugrundeliegende Logik ist identisch zu der PT1-Aufgabe. Einzig das neue fp-Interface muss genutzt werden.

Eine Spezifikation des ifstream-Interfaces ist erhältlich unter:
https://cplusplus.com/reference/fstream/ifstream/
Relevant sind hierbei die Methoden: fp.read(), fp.eof(), fp.isopen(). Da fp.read immer einen char* erwartet, kann reinterpret_cast genutzt werden um die Eingabedaten in den gewünschten Datentyp umzuwandeln.

Weiterhin müssen für die GradingTable zwei weitere Funktionen implementiert werden:
1. Der Destruktor der GradingTable muss den gesamten Inhalt der Liste korrekt wieder freigeben.
2. Die GradingTable soll für die Agenten einen Iterator implementieren. Iteratoren stellen eine Schnittstelle bereit, über die unkompliziert mittels einer for-Loop iteriert werden kann, ohne Abbruchbedingungen oder Zählvariablen verwalten zu müssen.

Für einen Iterator muss die Klasse einen Iterator-Datentyp bereitstellen, der den Zeiger auf das Listenelement speichert und alle nötigen Methoden bereitstellt:
- Der Iterator ist ein Struct, dass die Zählvariable (in diesem Fall ein Zeiger auf das aktuell betrachtete Objekt der Liste) und mehrere Zugriffsmethoden auf diesen bereitstellt.
- Der Iterator überlädt folgende Operatoren:
- operator*, um beim Auflösen des Iterators direkt auf das interne Objekt zuzugreifen. *iterator soll also nicht den Iterator zurückgeben, sondern das Element der Liste.
- operator-> funktioniert analog zu *, der Aufruf iterator->attribut sollte also auf das Attribut des Objekts auflösen.
- operator++ lässt den Iterator auf das nächste Objekt zeigen und gibt dann das neu referenzierte Objekt zurück.
- operator++(int) lässt den Iterator ein Element weiterspringen und gibt das VORHER referenzierte Objekt zurück.
- operator== überprüft ob sie auf dasselbe Element zeigen.
- operator!= ist das Inverse von ==.

Der Klasse GradingTable muss weiterhin zwei Methoden bereitstellen:
- begin() gibt einen Iterator zurück, der auf das erste Element der Liste verweist.
- end() gibt einen Iterator zurück, der identisch ist zu einem Iterator der das Ende der Liste bereits erreicht hat.

Wird mit for auf einen Iterator zugegriffen, wird zuallererst die begin()-Methode aufgerufen um den Iterator zu erzeugen. Danach wird mit operator++ je ein Element der Liste abgefragt. Mit end() wird ein fertiger Iterator erzeugt. Die Schleife bricht ab, sobald der Vergleich des Rückgabewerts von end() und des aktiv genutzten Iterators zu true auswertet.

## Aufgabe 2 - TaskAgents (4 Punkte)

Die so erzeugte GradingTable soll für die Auswertung genutzt werden. Dafür sind 2 Arten von TaskAgents zu implementieren. Einfache TaskAgents iterieren über die Liste, und rufen mit jedem Element der Liste visit() auf um dieses spezifische Element auszuwerten. Es werden keine Informationen über mehrere Elemente aggregiert, dafür wird der Rückgabewert jedes Aufrufs in einem Array gespeichert, wenn dieser Rückgabewert ungleich 0 ist.

Die ReducingTaskAgents aggregieren eine Eigenschaft der Listenelemente. Hierzu werden die beiden Methoden reduceAll() und reduce() genutzt. reduceAll() ruft reduce() für jedes Element der Liste auf, gemeinsam mit dem Rückgabewert des letzten reduce()-Aufrufs. Der Rückgabewert dieses Aufrufs wird dann dem nächsten Aufruf übergeben.

Beide Agenten implementieren die Methode performTask(), welche den jeweiligen spezifischen Auftrag auslöst. Dazu müssen die Schlüsselwörter virtual und override genutzt werden um die Methoden korrekt zu definieren. Weitere Informationen finden Sie in der Datei für diese Aufgabe.

Für beide Aufgaben sind die Interfaces größtenteils vordefiniert, bei manchen Methoden muss jedoch das Interface an den markierten Stellen noch um Rückgabedatentypen oder Parameter vervollständigt werden. Die Main-Funktion enthält bereits die Logik zum Parsen der Parameter und öffnen der Datenbankdatei.

Es sollen folgende 5 Agenten verfügbar sein:
- 'a': Soll für alle Element der Liste die Punkte ausgeben.
- 'b': Soll nur jene Ergebnisse ausgeben, deren Punkte unter 10 liegen. Für diese ist die Matrikelnummer anzugeben.
- 'c': Ein ReducingTaskAgent, der die Anzahl der Elemente zählt
- 'd': Ein ReducingTaskAgent, der die höchste erreichte Punktzahl bestimmt
- 'e': Ein ReducingTaskAgent, der die insgesamt in Series 3 bestimmten Punkte erfasst.
