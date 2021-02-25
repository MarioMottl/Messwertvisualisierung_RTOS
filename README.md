# Messwertvisualisierung_RTOS


### Es soll eine nicht blockierende Version der SvVis Library implementiert werden, die eine Messwertvisualisierung für Echzeitsysteme erlaubt. Visalisierung der Messdaten (Logging) über ein Acquisition on Event ausgelöst werden können. Die Messdaten werden in einen Ringbuffer geschrieben , von wo sie von einem Sende Thread abgeholt werden, der sie dann über den UART zu einem PC sendet. Der PC kann auch Kommandos an des Messsystem Senden, die entsprechend interpretiert werden. (z.B.: ACQ_On, ACQ OFF). Das System soll auch funktionieren, wenn PC sehr langsam ist (niedrige Baudrate). 

