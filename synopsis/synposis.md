# 01

## Def Betriebssystem: 

- Programme + Eigenschaften einer Rechenanlage, insbesondere Abwicklung und Steuerung von Programmen.
- "Like a government", provide an environment within other programs can do useful work.
- Bindeglied Software - Hardware

## Speicherhierarchie

Register - Cache - Hauptspeicher - SSD - Magnetische Disk - Optische Disk - Magnetbänder

## Architektur

### Einprozessorsysteme

- CPU <- Daten, Interrupt, IO -> Gerät
- CPU <- Instruktionen, Daten -> Speicher
- Gerät <- DMA -> Speicher

### Mehrprozessorsysteme

Symmetrisch: Jeder Prozessor eigene Kopie von OS
Assymetrisch: Zuoordnung von Tasks auf Prozessoren (Scheduling)

### Clustersysteme

Sammlung von Rechnern, gemeinsamer Speicher + Verbindung, gegenseitige Überwachung

### Sonstiges

Verteilte Systeme: Verteilung auf heterogene Rechnersysteme, lose Kupplung, Client/Server
Cloud Computing: IaaS, public/private cloud, on-demand

## Betriebssystemtypen

Stapelverarbeitung: Befehle auf Band, keine Interaktion
Serversysteme: Service-sharing (Drucker, ...), Multi-user
Multiprozessor: Anpassungen von Serversysteme für Multiprozessorsetup
PC-Betriebssysteme: Häufig nur ein Nutzer, einfache Oberfläche, viele IO / HID Geräte
Handheld Systeme: Teils Realtime, ereignisgesteuert
Embedded Systeme: Klein, effizient
Sensorsysteme: Energieeffizient, ereignisgesteurt
Echtzeitsysteme: Messgeräte, Roboter, Zeitschranken
Smart-Card Systeme: ...

# 02

## Systemkonponenten

Prozessverwaltung, Hauptspeicherverwaltung, IO Systeme, Kommunikationssysteme, Sekundärspeicherverwaltung, Schutz und Sicherheit, Resourcenverwaltung allgemein(CPU, Memory, Disk)

## Dual-Mode

User-mode für Anwendungen, System-mode für privilegierte (IO disk, memory, ...) Instruktionen.
Wechsel User -> System via trap oder interrupt
Wechsel System -> User durch System (reset Modus-Bit)


## Systembibliotheken

Bilden Interface zwischen Prozessen und OS, stellen Funktionen bereit die zB System-Calls enthalten.

## Systemprogramme

Umgebung für Entwicklung und Ausführung, Arbeit, ... (ls, cp, gcc, ...)

## Betriebssystemarchitektur

Monolithisch (Linux, Solaris, Windows): Grupperiung aber keine Modularisierung, jeder kann jeden aufrufen
Geschichtet (OS X): A la TCP
Mikrokerne: Auslagerung Teils des OS in Server (evtl User-Space) -> Kleiner Kernel
Ereignisgesteuert: Klar
VM: Klar

# 03

## Prozess

Code, Stack, Heap
Neu / Rechnend / Blockiert / Bereit / Beendet

### Prozessleitblock

Zeiger / Zustand / Nummer / BfZähler / Register / ...

Verkettete PLBs bilden Warteschlange (doubly-linked-list)

## Thread

Leichter Prozess, eigener Stack, teilt a) Code b) globale Daten c) OS Resourcen
Task == Ansammlung von Threads. (Ein Prozess = Task + 1 Thread)

Zustände wie bei Prozessor.

Thread kann arbeiten während andere Threads der Task blockiert. Effiziente Kontextwechsel (100x schneller als bei Prozess)
Aber: Scheduling auf Prozess-Stufe, d.h. Threads unsichtbar gegenüber OS - kein Schutz vor Starvation.

Bsp Browser mit Fenstern / Download Threads etc. Editor mit 1 Thread Formatierung, 1 Eingabe, ...

### User Threads

Thread library, gleicher Adressraum, transparent gegen OS, müssen CPU freiwillig aufgeben

### Kernel Threads

Von OS gemanaged, scheduling innerhalb Adressraum (z.B. bei blockierendem Thread)

### Hybride Threads

Multiplexing von user threads auf kernel threads. Normalerweise N:M

### Thread Pools

Spawnen von worker-Threads bei Start zwecks Vermeidung Overhead


## Scheduling

Job Queue: Auf Massenspeicher abgelegte Prozesse (waiting to load)
Ready Queue: Prozesse bereit im Hauptspeicher
IO Queue: Prozesse die auf IO warten
Ausgelagerte Prozesse: Swapped

Scheduler: Wählt Prozess. 

Dispatcher: Gibt Kontrolle an Prozess. (Speichert / lädt basierend auf PLB). Overhead 1-1000 micro-s

# 04

Prozessausführung: CPU Burts + IO Bursts

## Scheduler

Wählt aus Ready-Queue jenen, der laufen soll.

Entscheid bei Wechsel:
- Running -> Blocked (non-preemptive)
- Running -> Ready (preemptive)
- Blocked -> Ready (preemptive)
- Process terminates (non-preemptive)

Kriterien: Fairness, CPU Last, Durchsatz, Wartezeit (Ready-Queue), Verweilzeit (Lebenszeit), Realzeitverhalten, ...

### Schätzung CPU Burst

z.B. exponentieller Mittelwert: `t_n+1 = a * t+n + (1 - a) * t+n`

### FCFS

Nicht präemptiv.
Trivial

### Shortest Job First

Nicht präemptiv: Keine Verdrängung
Präemptiv: Verdrängung

### Priorität

Priorität basierend auf Speicherbedarf, EA, Wichtigkeit, ...
Problem: Aushungern. Lösung: Aging, Priorität steigt mit Wartezeit
Präemptiv oder nicht.

### Round Robin

Gut für Time-Sharing
Jeder Prozess erhält Zeitquantum. Nach Ablauf, Einreihung in Ready-Queue.
Präemptiv

### Multilevel

Mehrere Queues, jede Queue eigenes Scheduling, Aufteilung zwischen Queues mit Zeitscheiben

### Multilevel Feedback

Mehrere Queues mit verschiedenen Zeitquanti. Präemptiv

### Lotterie

Verlosung von Zeitquanti, Lose können zB von Client and Server gegeben werden

### Garantiertes Scheduling

vorgesehene zeit = (aktuelle zeit - Erzeugungszeitpunkt) / Anzahl Prozesse
verbrauchte Zeit / vorgesehene Zeit = x
Wähle Prozess mit kleinstem X
Präemptiv

### Echtzeit

Planbar falls:
Summe `(cpu_zeit_i / dauer_i) kleiner gleich 1`

#### Offline Scheduling

Scheduling vor Start. Voraussetzung: Periodische Aktivitäten

#### Earliest Deadline First

Prozess mit engster Frist selektiert
Präemptiv / Nicht präemptiv

# 05

## Prozessinteraktion

- Speicherbasiert (shared memory) -> synchronisation notwendig
- Nachrichtenbasiert (sync / async, ...): Via Mailbox oder direkt
  - Synchron: 0 Kapazität: Erfordert direkte Synchronisation
  - Async endlich: Sender wartet falls voll, Empfänger falls leer
  - Async unendlich: Keine Wartezeiten

## Kritischer Abschnitt

Folge von Code-Anweisungen mit Zugriff auf gemeinsame Daten.
Anforderung: Wechselseitiger Ausschluss, Fortschritt, Begrenztes Warten

### Semaphore

Zählende: Initialisiert auf Anzahl Resourcen. wait() zählt runter, signal() hoch.

### Monitor

Sammlung von Prozeduren, Variablen, Datenstrukturen. Innerhalb Monitor zu jedem Zeitpunkt nur ein aktiver Prozess.

# 06

## Verklemmungen

A belegt Mittel das von B benötigt wird, B belegt Mittel das von A benötigt wird

Treten auf, wenn alle auftreten:
- Wechselseitiger Ausschluss (Resource nur von einem Prozess nutzbar)
- Halten und Warten: Prozess der Resource hält wartet auf andere
- Keine Verdrängung: Resource nur frewillig freigebbar
- Zirkluierendes Warten: Pi wartet auf Pi+1 mod n

### Verhindern

Verhindern dass eine der vier Bedingungen zutrifft

Wechselseitiger Ausschluss: Nicht nötig für teilbare Resourcen
Halten und Warten: Belegen aller Resourcen vor Ausführung / Abgabe aller Mittel bevor neue belegt
Keine Verdrängung: Entzung von zugeweisenen Resourcen
Zirkulierndes Warten: Anordnung

### Vermeiden

Für jeden Zugriff entscheiden ob dadurch Verklemmung auftreten könnte

- Jeder Prozess beschreibt maximal verwendete Resourcen
- Anfrage erfüllt wenn in sicheren Zustand bleibt (keine Verklemmunge möglich)

#### Bankers

Geeignet für Resourcen mit mehrfachen Instanzen
- Available[j] = k von j verfügbar
- Max[i, j] = Pi nutzt maximal k von j
- Allocation[i, j] = Pi nutzt aktuell k von j
- Need[i, j] = Max[i, j] - Allocation[i, j] = Pi nutzt maximal k von j zustätzlich

### Aufheben

Erlauben dass auftritt, dann Massnahme ergreiffen

# 07

## Dynamisches Laden

- Aufgerufene Routine checkt ob aufgerufene Routine geladen. Wenn nicht: Loader lädt nach.
- Nützlich falls grosse Codesegmente selten benötigt
- User-Space Implementation möglich

## Dynamisches Binden

- Stub ist Stv für aufgerufene Routine
- Prüft ob Routine geladen, lädt wenn nicht
- Ersetzt sich selbst mit Routine
- Bibliotheksupdates ohne Compilierung/Linkung
- Dynamic Link Library / SHared Library
- Teilen von Code-Segmenten
- Erfodert OS, da Wissen über geladene Routinen dort

## Logische und Physikalische Adressen

- Physikalisch: 0 - n auf RAM
- Logisch: 0 - m in Prozessbereich.
- Logisch + Offset = Physikalisch
- Limit-Register: Logische Adresse kleiner Limit (0-basiert)

## Hauptspeicherverwaltung

- Linked lists, zB Bitmaps (frei / belegt)
- Allocation: Schnell, wenig verschnitt, ...
- First Fit, Next fit (Fortsezten bei Ende letzter Suche), Best fit, Worst fit, Quick fit (Liste mit üblichen Löcheern)
- Buddy System: Blöcke sind Potenzen von 2. Kein externern, sondern nur interner, Verschnitt. Sehr schnell.

## Paging

Nicht-zusammenhängender physikalischer Adressraum.

- Aufteilung physikalischer Speicher in Kacheln (Frames, 2*n Bytes)
- Logischer Speicher in Pages (Gleiche Grösse)
- Paging-Table mapped Pages auf Frames
- Internet Verschnitt
- Paging Table per Prozess
- Adresse: Page number p, Page offset 0, Frame nr k

### Multi-level Paging

Problem: Seitentabelle wird gross. (2**32 Bytes, 4 KB Page, 2**20 Pages, 4 Bytes per table entry, 4MB Page table)

Lösung: Multi-level Paging. Logische Adresse = (p1, p2, 0), Lookup in mehreren Nested Tables

#### Two-Level paging

Klar

#### Page table with hashes

#### Inverted page table

Nur Einträge für reale (belegte) Frames, Aber: Aufwändigere Suche

## Segmentierung

- Compiler erstellt Segmente für lokale Variabeln, Stack, Prozedur A, Prozedur B, ....
- Jedes Segment mit eigenem Offset (+ Limit)
- Kombinierbar mit Paging

# 08

## Virtueller Speicher

- Benötigte Teile eines Programms in Hauptspeicher, rest in Sekundärspeicher
- Grosser Speicherbereich
- Memory sharing
- Demand-Paging

## Demand Paging

- Pager lagert nur benötigte Pages ein (Weniger IO, weniger Speicherbedarf)
- Memory Access: Laden der Page von Disk nach Memory if nicht geladen
- Zugriff auf Page in Memory
- Copy-on-write für bessere Performance

### Paging Algorithmen

- FIFO: Trivial: Schlechte Performance
- LRU: Least recently used: Aufwändig
- Referenzbit (1 Bit: Second chance)
- Clock: 1 Ptr Auslagern, 1 Ptr zurücksetzen
- Second chance+: 2 Bit, 1 bit second chance, 1 bit unverändert / verändert

## Paging

- Page buffering: Freihalten eines Pools an freien Pages: Schnellere Einlagerung
- Schreiben Pages auf Speicher wenn Idle -> Eventuell schnellere Auslagerung später
- Thrashing: Mehr mit Paging beschäftigt als mit Arbeit: Prozess mehr Kacheln zuordnen
- Überwachung Page Faults: Anpassung Speicherzuordnung des Prozesses

# 09

## Disk-Anbindung

- Host-Anbindung: IDE, SATA, SCSI, ...
- Netz-Anbindung: LAN, RCPs, iSCSI
- SAN: Dediziertes Netz, spezielle Disk-Access Protokolle (Fibre-Channel, Infiniband, ...)

## Disk Formatierung

- Low-level / physikalisch: Unterteilen einer Disk in Sektoren. (Header - Data - Trailer)
- Logisch: Partitionen, Filesystems

### Partitionierung

- MBR: In Sektor 0
- Boot Block: Program das OS lädt
- Superblock: Datenträgeraufbau, Blockgrösse, ... Meta Informationen
- Freispeicherliste / Liste fehlender Blöcke

### Fehlerhafte Blöcke

- Sector Sparing: Liste schlechter Blöcke, transparente Umleitung auf Reserveblock -> Verschlechtertes Disk-SCheduling
- Sector Slipping: Verschieben von Sektoren um eine Spur

### RAID

- Schützt vor Hardwarefehlern, aber nicht Software (z.B fehlerhaftem Disk-Driver)
- Dort muss zB das FS (siehe ZFS) Abhilfe schaffen (Prüfsummen + Korrektur falls zB gespiegelt)

#### RAID 0

- Striping / Interleaving: Jede Disk hat Streifen der virtuellen Disk
- Block-level Striping: 1 Datei auf N Disks

#### RAID 1

- Mirroring

#### RAID 2

- Bit interleaving (7-bit hamming code)

#### RAID 3

- RAID 2 mit nur Parität (even or odd)

#### RAID 4

- Paritätsblöcke

#### RAID 5

- Verteilung & Parität

#### RAID 6

- Wie 5, aber mit mehr Redundanz

## Dateisysteme

- Lesen & Schreiben
- Attribute per Datei (Namen, Ort, ...)
- Multi-user

## Trivia

- mmap: Einbindung einer Datei als virtueller Speicher: Schreiben nach schliessen der Datei

# 10

## Dateisysteme

### Logisches Dateisystem

- Datei und Verzeichnisoperationen
- Verwalten von Dateien / Strukturen
- Schutzmechanismen

### Organisationsmodul

- Übersetzung logische in physikalische Adresse
- Freispeicherverwaltung
- Festplattenmgmt

### Basisdateisystem

- Kommandübergabe an I/O (Lese Disk 1, Zylinder 2, Spur 3, Sektor 4)
- Scheduling
- Caching

### I/O Steuerung

- Interface zu Gerätetreiber, Interrupts

## inode

- mode, link count, owner uid, gid, ...
- direct blocks (10) -> pointing to data blocks
- single indirect -> points to list of direct blocks
- double indirect -> points to list of single indirects
- triple indirect -> ....

## File table

- Systemweite Tabelle mit offenen Files
- Tracking welche Prozesse welche Files
- Datei öffnen: FCB wird in file table kopiert, ausgabe Deskriptor für Zugriff

## Verzeichnisse

- Liste mit Zeigern auf Dateiblöcke: Einfach, non-performant (Varianten: Bäume, sortierte Listen, ...)
- Hash-Tabelle: Berechnung Hash Wert aus Dateiname, dann Suche in Hash Bucket

## Allokation

### Zusammenhängend

- Einfache Implementierung
- Dateien können nicht wachsen
- Wahlfreier Zugriff
- Externer Verschnitt
- Allokation zB best, worst, ... fit

### Verkettete

- Datei ist Liste von Blöcken
- Beliebige Anordnung
- Sequenzieller Zugriff, aber nicht wahlfrei
- Keine Verschwendung
- Bei beschädigtem Block ganze Datei weg
- Beispiel: FAT. Unbenutzte mit 0 markiert

### Indizierte

- Alle Zeiger in Indexblock
- Wahlfreier Zugriff
- Kein Verschnitt
- Overhead durch Index Block

## Freispeicherverwaltung

- Bitvektoren / Bitmaps (0: Block Frei, 1: Block Belegt)
- Linked List (effizienter da nur freie gespeichert)
- Gruppieren: Erste n freie Blöcke in einem Block grupieren (Schnell für grosse Mengen freier Platz finden)
- Zählen: Linked list, Zeiger und Anzahl folgender freier Blöcke (inklusive Block selber)
- Space Maps: (ZFS): Partition in Metaslabs, jeder 1 Space Map = Log aller Aktivitäten (Allokation + Freigabe), Aufbau als z.B Baum

# 11

## E-A Software

- Programme die IO nutzen sollten geräteunabhängig sein
- Fehlerbehandlung hardwarenah
- Synchrone und Asynchrones IO
- Pufferung zwecks Entkopplung von physikalischer Lese/Schreib Geschwindigkeit
- Multi-User

## Programmierte IO

Beispiel: Drucker

- Prozess öffnet Device / blockiert bis nicht mehr benutzt
- Systemaufruf mit Ausgabedaten
- OS verarbeitet: Pufferung zu Device in Kern

## Interrput-Gesteuerter IO

- Prozessumschaltung zwischen einzelnen Zeichen möglich

## DMA-basierter IO

- Software übergibt Daten und Ziel (Write) bezw. Quelle und Datenmenge (Read)
  an DMA Controller
- DMA Controller handhabt Pufferung gegen und von Device
- Interrput sobald Write/Read vollständig

## IO Stack

### Gerätetreiber

- Gerätespezifisch
- Vom Hersteller bereitgestellt
- Initialisert Geräte, Anfragen an Gerät, Übersetzung OS <-> Gerät, Fehlerbehandlung, Leistungssteuerung, ...

### IO-Subsystem

- Einheitliche Schnittstelle für Applikationen
  - Gleiche Schnittstelle für Block- und zeichenorientierte Geräte
  - Unix: Geräte im Dateisystem inkl. access control, inode enthält Informationen für Device-Access
- Scheduling
  - Hohe Ausnutzung
  - Tiefe Wartezeiten
  - Queueing bei blockierendem Gerät
- Buffering
  - Input: Double-buffering in Kern
  - Output: Kopie der User-Daten in Kern-Buffer (freistellen des Applikations-Buffers), danach Senden an Device
- Access Control: IO Operationen nur von OS
- Error handling
- Einheitliche Blockgrössen: Verstecken der unterschiedliche Blockgrössen der Disks gegenüber Anwendungssoftware

### Block- vs zeichen-orientiert

- Block: zB Disks, speichern der Informationen als Block von zB 1KiB
  - read, write, seek
  - Dateisysteme / memory-mapping
- Zeichen: Eingabe / Ausgabe von Zeichenströmen, zB Tastatur
  - get, put
  - Buffering erlaubt zB 'one line at a time'

### Zeitoperationen:

- Clock: Lesen / schreiben der Systemzeit
- Timer: Lesen der Zeit seit Zeitpunkt
- Einsatz: Alarming, Scheduling, Profiling, ...
- Implementierung: Hardware-Uhr 10-100 Interrupts/s
  - Routine aktualisiert Systemzeit
  - Timer als Liste implementiert: Jedes Element hat 'Offset' zu vorhergehendem Element gespeichert
  - Bei jedem Interrupt: Offset des ersten Elementes entsprechend anpassen -> Ausführen falls `<=0`

### Sync/Async IO

- Blocking/Sync: Einfacher, Anwendung 'verdrängt' während IO Vorgang
- Nonblocking/async: Schwieriger zu implementieren, gebraucht für zB User Input mit gleichzeitiger Anzeige von Daten.
  - Implementierung mit zB separaten Threads
  - Implement with sync calls: select (check if IO possible), read, write
  - Alternative: Implementierung durch async Systemaufrufe -> Signal/Interrupt/Callback wenn abgeschlossen

# 12

## Virtuelle Maschinen

- Illusion: Mehrere getrennte Umgebungen auf einer physikalischen Maschine
- Emulation verschiedenster Hardware (inkl. Architekturen), zB MS-Dos in Windows, Java VM, ...
- Vorteile:
  - Sicherheit
  - OS Entwicklung (Einfachheit)
  - OS Wechsel
  - Bessere Ausnutzung Hardwarer / tiefere Managementkosten
  - Cloud
- Nachteile:
  - Kontextwechsel & Emulation erzeugt Overhead
  - Hardwareunterstützung erforderlich
- vCPU: Zustand der CPU je Gast, teilweise Ustü durch Hardware-CPU

## Sensitive vs Privilegierte Instruktionen

- Sensitiv: Unterschiede in User vs System-mode
- Privilegiert: Lösen Trap aus wenn in User-mode
- Virtualisierung bedingt dass Sensitiv Teilmenge von Privilegiert
  - Von alten CPUs nicht erfüllt (bsp popf @ i386: Kein Interrupt, keine Auswirkung in Usermode, ersetzt Interrupt-Flag in System-mode)
  - AMD Secure Virtual Machine / Intel Virtualization Technology erfüllt die Bedingung
  - Binary translation erlaubt auch non-virtualisierbare Systeme zu virtualisieren

## Dual-Mode bei VMs

- Hypverisor in realem Systemmodus
- Gast-OS in virtuellem Systemmodus, realem Benutermodus
- Gast Applikationen in virtuellem Benutzermodus, realem Benutzermodus
- x86: Vier Protection-Ringe -> Abbilden der drei Modi darauf

## Trap-and-emulate

- Aufruf privilegierter Instruktion in VM -> Trap -> Wechsel zu Hypervisor -> Durchführen der nötigen Instruktione -> Kontrolle zurück

## Binary Translation

- On-the-fly scanning des Programmes, identifikation von Basisblöcken (keine Sprünge, Traps, Subroutinen, ... bis auf letzte Instruktion)
- Ersetzen sensitive & letzter Instruktion durch Hypervisor-Prozeduren
- Jene Emulieren die ersetzten Funktionen
- Caching von Basisblöcken: Performance
- Teils effizienter als Hardware-unterstützte Hypervisor-Aufrufe

## Hypervisor-Typen

- Typ 0: Hardware-Lösung (Firmware) zB Lynxsecure
- Typ 1: OS-ähnliche Software oder OS-Erweiterung (zB Linux mit KVM, Xen, ...)
- Typ 2: Anwendung die on top of OS läuft (zB VMWare)
- Paravirtualisierung: Anpassung von Gastbetriebssystemen durch Hypervisor
- Anwendungs-Container: Isolation der Anwendung & Dependencies von OS (Docker)
- Applikations-VMs (JVM)
- Emulatoren (fremde Hardware)

### Typ 0

- Bootvorgang lädt Hypervisor aus Firmware, Hypervisor lädt VMs
- Hardware-Virtualisierung vom RAM/CPU
- IO Devices durch Gast-OS verwaltet, da Hypervisor keine Treiber hat

### Typ 1

- Spezial-OS (ESX, HyperV, Xen)
- Laufen in Systemmodus
- Implementieret Gerätetreiber, CPU Scheduling, Speicherverwaltung, ...
- Falls pure Hypervisor: Weniger Code als OS -> Weniger Bugs

### Typ 2

- Prozess läuft in Useremode
- Oft Kernel-Modul zwecks Ausführung privilegierter Instruktionen

### Paravirtualisiierung

- Modifizertes Gast-OS
- On-the-fly ersetzen von Instruktionen durch Aufrufe des Hypervisors

### Anwendungs-Container

- Anwendung hat Eindruck, dass einziger Prozess in System
- Nur Virtualisierung des OS und Geräte, nicht der Hardware
- Eigener Netzwek-Stack
- Eigenes Scheduling

## Virtualisierung von Speicher

- Eine Seitentabelle je VM
- Virtuelle Adresse - Virtuelle Seitentabelle -> Physikalische Gastadresse - Physikalische Seitentabelle -> Physikalische Adresse
- Updates auf Gast-Seitentabelle: Entweder abfangen der Abweisung und anpassen, oder Aktualisierung der Seitentabelle bei Page-Faults und Abfangen von Löschoperationen
- Hardware-Ustü in Prozessoren: Nested/Extended Page-Tables
- Paravirtualisierung: Benachrichtigung Hypervisor nach Anpassung Tabelle
- Over-commitment: Mehr zuordnen als verfügbar
- Ballooning: Anpassen der verfügbaren RAM Menge dynamisch, Treiber in jedem Gast nötig
- Teilen von gleichen Seiten zwischen Systemen (Hash)

## Virtualisierung von IO

- Problem: Jeder Gast geht von vollständiger Kontrolle aus -> zB Scheduling Probleme
  - Lösung: zb Disk: Mehrere Disk-Regionen, eine je Gast
- Vorteil: Abstraktion der unterliegenden Hardware, zB alte Treiber in Gast OS mit neuer Hardware
- Networking: Jeder Gast eigene IP, Hypervisor ist Switch

## DMA

- übersetzen der Adressen durch Page-Table der E/A-MMU, die je nach Gast vom Hypervisor gesetzt wird

## Live-Migration

- Kopie RAM, IP, ...
- Anhalten alter Maschine, erneuter Sync RAM
- Starten neuer Maschine
- Migration Sekundärspeicher dank zB NFS nicht nötig

# 13 Sicherheit

- Ziele: Confidentiality (Vertraulichkeit, Daten geheim), Integrity (Daten nicht veränderbar), Availability (Daten nicht störbar), Access control (Zugriffskontrolle)
- Massnahmen: Phsyikalischer Schutz, Authentifizierung bei Zugriff, Schutz vor Sicherheitsverletzungen, Schutz auf Netzwerkebene, ...

## Zugriffsrechte

- Protection: Kontrolle des Ressourcen-Zugriff
- Policies: Regeln
- Domains: Menge von Objekten mit Policies (Domain zB User, Prozess, ...)
- Unix: Domain = user
- Zugriffsmatrix: Spalten = ACLs (zB File1, Printer2, ...), Zeilen = Domains
- ACL: Je Objekt, welche Domain welche Rechte? (zB D1 R, D2 RW, D3 X, ...)
- Capabilities: Liste von Policies je Domain, zB (F1 R, F2 RW, P1 RW, ...)
- Rolle: Sammlung von Policies, kann an User / Prozess / ... Domain zugeordnet werden

## Authentifizierung

- Identifizierung des Kommunikationspartners: Schlüssel, Passwort, Service (Kerberos), Biometrisch, physikalisch, ...
- Passwort: Speichern als Hash, so dass kein Klartext. Hash mit Salt, so dass keine Rainbow-Tables
- OTP: Passwortlisten (aber doof), deshalb:

### Lamport

- Client wählt Secret s
- P_(n-1) = f(P_n)
- Client bereitet zB 1000 Passwörter vor, teilt Server P_1000 mit, dieser speicher P_1000.
- Login: Client schickt Server P_999, Server schaut ob f(P_999) = P_1000, falls ja: io, speichert P_999
- Wenn 

### Kerberos

- Nonce [N]: Integer zwecks Anzeige der Aktualität einer Nachricht (Sequenz, Uhrzeit, ...)
- Ticket: Von Ticket-Granting-Server (TGS) ausgestellt. Zeigt, dass Client vor kurzem bei TGS authentisiert
  - Lifetime & Session key
  - Mit private key verschlüsselt
- Authenticator:
  - Von Client erstelltes Token, enthlält Client Name [C] + Zeitstempel [t]
  - Verschlüsselt mit Sitzungsschlüsel
  - Einmal nutzbar
- Session key: Von Kerberos ausgestellt, per-client, per-Kommunikation

### Physikalisch

- Karte mit Magnetstreifen der zB Passwort enthält
- SmartCard (CPU, ROM, RAM): Challenge-Response (zB Zufallszahl - SC berechnet Antwort aus Zahl und Seret, sendet an Server)

### Biometrisch

- Aufnahme Daten
- Identifikation: Messung, Vergleich mit gespeicherten/bekannten Daten
- Fingerabdrücke, Iris, Unterschrift, ...

## Angriffe

- Von innen
- Ausnutzen von Bugs
- Malware

### Von innen

- Annahme: Angreifer in Rechner
- Login-Spoofing
- Logische Bomben (inaktiv solange zB Entwickler sich täglich anmeldet)
- Backdoors in Programmen (zB Access ohne Passwort)

### Ausnutzung von Bugs

#### Buffer-Overflow

- Zugriff auf uninitialisierter Speicherbereich
- zB: Applikation hat Buffer mit Grösse 1k
  - Übergabe 2k Daten
  - Überschreiben 'zufälliger' Daten, zB Rücksprungadresse
  - Umleitung Kontrollfluss zu Gunsten Angreifer
- Gegenmassnahmen:
  - Canaries: Compiler fügt Code ein der bei Routinen-Aufruf zufällligen Wert auf Stack schreibt, überprüft bei Rückkehr, ob Canary verändert
  - Data Execution Prevention: CPU verbietet Ausführung von Code auf Heap od Stack

#### Code-Reuse

- Kombination von existierenden Code-Snippets zwecks Konstruktion Schadcode (via Modifikation Return-Adressen)
- Gegenmassnahme: Address space layout randomization

### Schadsoftware

- Angriffe via Netze zB Internet
- Transfer Code auf Zielmaschine, danach ausführen

#### Trojanische Pferde

- Harmlos erscheinendes Programm mit ungewünschter Funktionalität
- zB via Freeware
- Oder überschreiben von Programm mit Verzeichnis das in $PATH ist

#### Viren

- Reproduzieren indem sie ihrene Code verbreieten (zB E-Mail, SMB, USB, ...)
- Boot-Sektor, Gerätetreiber, Source-Code, Companion- ... Viren
- Scanner: 
  - Durchsucht executables nach bekannten Signaturen (Problem: Polymorphe Viren)
  - Verifiziert Länge von executables (Problem: Kompression Viren)
  - Prüfsummen verifizieren (Problem: Manipulation durch Viren, lösbar mit zB Verschlüsselung)
  - Verhalten prüfen (zB Zugriff Boot-Sektor, ...)

#### Würmer

- Bootstrap-Wurm: Lädt eigentlichen Schadcode nach (Bootstrap-Wurm klein)
- Remote shell, sendmail, ...
- Abwehr: Signaturen (verdächtige Datenflüsse), Netzwerk-Filter

#### Spyware

- Sammelt Benutzeraktiviät
- Ändert Einstellungen (zB Suchmaschine)

#### Rootkits

- Sammlung von Programmen die zB Administrator-Rechte erlangen
- Verberegen Existenz (Verstecken in Firmware, Kern, ...)
- Erkennen durch Signaturen
- Entfernen durch Neuinstallation ;)

# 14 Distributed File Systems

- Mehrere Nutzer teilen Datei- und Speicher-Resourcen
- Keine Unterscheidung lokaler vs entfernter Daten
- Server: Dateisystem-Software (NFS, SMB, ...)
- Client: zB FS Treiber der create, delete, ... auf entsprechende Aktionen mapped

## Anforderungen an DFS

- Access transparency: Applications should not be able to distinguish between local and remote files (equal operations)
- Location transparency: Location should not distinguish between local and remote files (e.g. in path, ...)
- Mobility transparency: Moving a file between local and remote storage should not incur additional modifications to the system- Performance transparency: Performance should not depend on load (ha-ha)
- Scaling transparency: DFS should be extendable
- Security (access control)
- Replication (eh?)
- Consistency

## RPC

- eg NFS: Reading/writing/... of remote files
- Local: Stub implementation of server which forwards calls to remote server
- Server: Stub implementation of client which forwards calls to remote client

## Caching

- Better performance and less bandwith usage by e.g. caching files locally (also by caching local files in RAM)
- But: Consistency with master copies has to be ensured
- Caching in Disk: Cheap, robust (e.g. caching remote files)
- Caching in Memory: Fast (e.g. caching disk IO)
- Caching in Application: Special cases, e.g. kernel

### Cache refreshing

- Write-through:
  - Writing when source modified
  - Caching for read access
  - Robust
  - eg NFS meta data (directories, attributes)
- Delayed write / write back:
  - Delayed writing when source modified
  - Caching for write access, too
  - less robust
  - Write-Back: Write cache when removed from client cache (but: blocks can be in cache long: not robust)
  - Scan cache: Periodic checking of cache, refreshing changed blocks (e.g NFS for files)
  - Write-on-close: Good for files which are seldomly changed, or opened for short amounts of time (e.g Andrew FS)

### Consistency

- Client-oriented: Client initiates consistency check of cached and master file
  - on first access
  - on each access
  - periodical
- Server-oriented: Server tracks client records, ie information of cache copies
  - Notifies client in case of possible inconsistency

### Zustands-behaftet / -los

#### Zustandsbehaftet

- Tracking of accessed files (per client)
- On access, file is loaded into cache
- Future access is served from (and to?) cache
- eg NFSv4
- Client crash: Has to inform server

#### Zustandslos

- Returning of requested blocks
- No tracking of open files needed
- Direct writing of sent files
- More robust to client/server crashes
- eg NFSv3

### Server Caching

- Unix: Read-ahead: Blocks following currently-read ones are read too, and loaded into cache
- Unix: Delayed write: Write first goes into cache, flushed to disk if either cache low, or every n seconds as bulk
- NFSv3: Write-through caching:
  - Output: Before sending reply to client, change is persisted to disk
  - Input: Inbound changes written to cache, only saved to disk once commit from client received
  - This ensures that, if the client crashes the file remains untouched, and if the server crashes, the changes persist
- NFS: Caching of results of read/write/getattr/lookup/readdir
- Problem: Zeitversetzter write() eines anderen Clients führt zu Mix: Zeitstempel der Changes hilft

## Access control

- Check of credentials on each access
- Old NFS: user/group in each RPC call
- Comparison of user/group ID with user/group of file
- Optional: DES encryption, Kerberos authentication
