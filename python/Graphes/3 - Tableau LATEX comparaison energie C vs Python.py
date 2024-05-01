# Consommation d'énergie en watts
consommation_python = [10, 15, 20]  # Exemple de consommation d'énergie Python pour 7, 50 et 100 points
consommation_c = [5, 8, 12]  # Exemple de consommation d'énergie C pour 7, 50 et 100 points

# Tailles de vecteurs de points en binaire
tailles_vecteurs = ['7 points', '50 points', '100 points']

# Génération du code LaTeX pour le tableau
tableau_latex = "\\begin{table}[ht]\n"
tableau_latex += "\\centering\n"
tableau_latex += "\\begin{tabular}{|c|c|c|}\n"
tableau_latex += "\\hline\n"
tableau_latex += "Taille du vecteur & Consommation d'énergie (Python) & Consommation d'énergie (C) \\\\\n"
tableau_latex += "\\hline\n"

for taille, conso_py, conso_c in zip(tailles_vecteurs, consommation_python, consommation_c):
    tableau_latex += f"{taille} & {conso_py} W & {conso_c} W \\\\\n"

tableau_latex += "\\hline\n"
tableau_latex += "\\end{tabular}\n"
tableau_latex += "\\caption{Comparaison de la consommation d'énergie entre Python et C pour différentes tailles de vecteurs de points en binaire.}\n"
tableau_latex += "\\label{tab:comparaison_energie}\n"
tableau_latex += "\\end{table}"

print(tableau_latex)
