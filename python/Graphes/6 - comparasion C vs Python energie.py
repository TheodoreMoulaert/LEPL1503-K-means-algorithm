import matplotlib.pyplot as plt

# Tailles de fichiers
tailles_fichier = ["7 points", "50 points", "100 points"]

# Données de consommation d'énergie pour Python (exemples)
energie_python = [50, 100, 150]  # Exemple de liste de consommation d'énergie pour Python
energie_C = [30, 80, 120]  # Exemple de liste de consommation d'énergie pour C

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
