#DONE

import matplotlib.pyplot as plt

# Tailles de fichiers
tailles_fichier = ["7 points", "50 points", "100 points"]

# Données de consommation d'énergie pour Python (exemples)
energie_python = [0.00018159,0.001023238,0.003079368]  # Exemple de liste de consommation d'énergie pour Python
energie_C = [0.00000726639, 0.0000557931, 0.000119634]  # Exemple de liste de consommation d'énergie pour C

# Création du graphique
plt.figure(figsize=(10, 6))

# Tracé des lignes pour la consommation d'énergie de Python et de C
plt.plot(tailles_fichier, energie_python, label='Python', marker='o')
plt.plot(tailles_fichier, energie_C, label='C', marker='o')

# Configuration du graphique
plt.title("Comparaison de la consommation d'énergie entre C et Python")
plt.xlabel("Taille du fichier")
plt.ylabel("Consommation d'énergie [W]")
plt.grid(True)
plt.legend()

# Affichage du graphique
plt.tight_layout()
plt.show()
