import psutil
import csv
import time
import os
import argparse

# Funktion zum Schreiben der Ressourcennutzung in eine CSV-Datei
def log_resource_usage(process, csv_file, interval=1):
    # Überprüfen, ob die Datei bereits existiert (für Kopfzeile)
    file_exists = os.path.isfile(csv_file)

    with open(csv_file, mode='a', newline='') as file:
        writer = csv.writer(file)

        # Kopfzeile nur schreiben, wenn die Datei neu ist
        if not file_exists:
            writer.writerow(["Timestamp", "CPU Usage (%)", "Memory Usage (MB)"])

        # Überwachung starten
        while True:
            # Überprüfen, ob die Stop-Datei existiert
            if os.path.isfile("stop.txt"):
                print("Stop-Flag gefunden. Beende Überwachung.")
                break

            try:
                # CPU und Arbeitsspeicher für den Prozess abrufen
                cpu_usage = process.cpu_percent(interval=1) / psutil.cpu_count()  # Prozent
                mem_info = process.memory_info()
                memory_usage = mem_info.rss / (1024 * 1024)  # In MB

                # Zeitstempel hinzufügen
                timestamp = time.strftime("%Y-%m-%d %H:%M:%S")

                # Daten in die CSV-Datei schreiben
                writer.writerow([timestamp, cpu_usage, memory_usage])

                print(f"Timestamp: {timestamp}, CPU Usage: {cpu_usage}%, Memory Usage: {memory_usage:.2f} MB")

                # Wartezeit bis zur nächsten Messung (z.B. alle 10 Sekunden)
                time.sleep(interval)

            except (psutil.NoSuchProcess, psutil.AccessDenied, psutil.ZombieProcess):
                print("Prozess nicht gefunden oder Zugriff verweigert.")
                break


# Hauptprogramm
if __name__ == "__main__":
    # Argumentparser einrichten, um den CSV-Dateinamen als Argument zu akzeptieren
    parser = argparse.ArgumentParser(description='Überwache die Ressourcennutzung eines Prozesses und logge sie in eine CSV-Datei.')
    parser.add_argument('csv_file', type=str, help='Der Name der CSV-Datei, in die die Daten geschrieben werden sollen')
    parser.add_argument('express_pid', type=int, help='Die PID des zu überwachenden Prozesses')

    # Argumente parsen
    args = parser.parse_args()

    # Prozess und CSV-Datei von den Argumenten verwenden
    process = psutil.Process(args.express_pid)
    if process:
        print(f"Überwache Ressourcen für Prozess:  PID: {process.pid}")
        log_resource_usage(process, args.csv_file)
    else:
        print(f"Node.js Prozess express nicht gefunden.")