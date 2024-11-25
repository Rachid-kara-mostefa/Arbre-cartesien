

Q2.b
La complexité de l'algorithme de recherche dans un arbre cartésien est directement liée à la profondeur du nœud recherché (ou de son successeur/prédécesseur si la recherche est infructueuse).
Analyse de la complexité
Recherche fructueuse
La recherche suit le chemin depuis la racine jusqu'au nœud contenant la clé.
Le nombre de comparaisons effectuées est égal à la profondeur du nœud recherché dans l'arbre.
Si la profondeur du nœud est hhh, la complexité de la recherche est O(h)O(h)O(h).
Recherche infructueuse
La recherche suit le chemin depuis la racine jusqu'à une position où la clé aurait été insérée (soit une feuille ou un nœud sans sous-arbre à gauche ou à droite).
Dans ce cas, la complexité dépend également de la profondeur du successeur ou du prédécesseur, car ce sont les nœuds visités en dernier avant d'abandonner la recherche.
Si la profondeur de ce point est hhh, la complexité reste O(h)O(h)O(h).
Profondeur hhh en fonction du nombre de nœuds nnn
Pour un arbre parfaitement équilibré, h≈log⁡2(n)h \approx \log_2(n)h≈log2​(n), donc la complexité moyenne est O(log⁡n)O(\log n)O(logn).
Dans le pire cas (arbre dégénéré, comme une liste chaînée), h=nh = nh=n, donc la complexité est O(n)O(n)O(n).
Conclusion
La complexité dépend de hhh, la profondeur du nœud recherché ou du point où la recherche s'arrête :
Meilleur cas (arbre équilibré) : O(log⁡n)O(\log n)O(logn).
Pire cas (arbre dégénéré) : O(n)O(n)O(n).
