import numpy as np

# Temps d'exécution en secondes
temps_python = [0.287666667, 1.236333333, 3.720666667]  # Exemple de temps d'exécution Python pour 7, 50 et 100 points
temps_c = [0.014, 0.104666667, 0.198333333]  # Exemple de temps d'exécution C pour 7, 50 et 100 points

# Tailles de vecteurs de points en binaire
tailles_vecteurs = ['7 points', '50 points', '100 points']

# Génération du code LaTeX pour le tableau
tableau_latex = "\\begin{table}[ht]\n"
tableau_latex += "\\centering\n"
tableau_latex += "\\begin{tabular}{|c|c|c|}\n"
tableau_latex += "\\hline\n"
tableau_latex += "Taille du vecteur & Temps d'exécution (Python) & Temps d'exécution (C) \\\\\n"
tableau_latex += "\\hline\n"

for taille, temps_py, temps_c in zip(tailles_vecteurs, temps_python, temps_c):
    tableau_latex += f"{taille} & {temps_py:.2f} & {temps_c:.2f} \\\\\n"

tableau_latex += "\\hline\n"
tableau_latex += "\\end{tabular}\n"
tableau_latex += "\\caption{Comparaison des temps d'exécution entre Python et C pour différentes tailles de vecteurs de points en binaire.}\n"
tableau_latex += "\\label{tab:comparaison}\n"
tableau_latex += "\\end{table}"

print(tableau_latex)
