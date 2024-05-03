# Consommation d'énergie en watts
consommation_python = [1.8159*10**-4, 1.023238*10**-3,3.079368*10**-3 ]  # Exemple de consommation d'énergie Python pour 7, 50 et 100 points
consommation_c = [7.26639*10**-6, 5.57931*10**-5, 1.19634*10**-4]  # Exemple de consommation d'énergie C pour 7, 50 et 100 points

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
