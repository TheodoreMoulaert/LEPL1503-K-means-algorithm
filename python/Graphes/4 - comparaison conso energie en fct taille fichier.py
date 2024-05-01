import matplotlib.pyplot as plt

# Tailles de fichiers
tailles_fichier = ["7 points", "50 points", "100 points"]

# Données de la consommation en énergie pour chaque taille de fichier
energie_7_points = [10, 20, 30]  # Exemple de liste de consommation en énergie pour 7 points
energie_50_points = [50, 100, 150]  # Exemple de liste de consommation en énergie pour 50 points
energie_100_points = [100, 200, 300]  # Exemple de liste de consommation en énergie pour 100 points

# Calcul de la consommation en énergie min et max pour chaque taille de fichier
energie_min = [min(e1, e2, e3) for e1, e2, e3 in zip(energie_7_points, energie_50_points, energie_100_points)]
energie_max = [max(e1, e2, e3) for e1, e2, e3 in zip(energie_7_points, energie_50_points, energie_100_points)]

# Calcul de la consommation en énergie moyenne pour chaque taille de fichier
energie_moy = [(e1 + e2 + e3) / 3 for e1, e2, e3 in zip(energie_7_points, energie_50_points, energie_100_points)]

# Création du graphique
plt.figure(figsize=(10, 6))

# Tracé des lignes verticales entre consommation en énergie min et max pour chaque taille de fichier
for i, taille in enumerate(tailles_fichier):
    plt.plot([taille, taille], [energie_min[i], energie_max[i]], color='blue', linewidth=2)
    plt.scatter(taille, energie_min[i], marker='o', color='green', label='Consommation min' if i == 0 else "")
    plt.scatter(taille, energie_max[i], marker='o', color='red', label='Consommation max' if i == 0 else "")
    plt.plot(taille, energie_moy[i], marker='o', markersize=5, color='orange', label='Consommation moyenne' if i == 0 else "")

# Relier les points moyens jaunes entre eux
plt.plot(tailles_fichier, energie_moy, color='orange')

# Affichage des annotations
for i, txt in enumerate(tailles_fichier):
    plt.annotate(f"Moyenne: {energie_moy[i]:.2f}", (tailles_fichier[i], energie_moy[i]), textcoords="offset points", xytext=(0,10), ha='center')

# Configuration du graphique
plt.title("Consommation en énergie en fonction de la taille du fichier")
plt.xlabel("Taille du fichier")
plt.ylabel("Consommation en énergie [W]")
plt.xticks(tailles_fichier)
plt.grid(True)
plt.legend()

# Affichage du graphique
plt.tight_layout()
plt.show()
