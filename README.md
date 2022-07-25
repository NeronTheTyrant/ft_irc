# TODO

- Lire la doc : http://chi.cs.uchicago.edu/chirc/index.html 
- Structure Principale
- Gestion User
- Gestion Channel
- Gestion Operator
- Parser
- Commandes
- Gestion connexion / deconnexion propres
- Gestion d'erreur propre
- Log de serveur
- Implementation de SharedPtr

# Guidelines

- Utilisez des pull request et des fix tickets autant que possible (faut apprendre comment faire)
- Gardez une norme commune (voir Norme plus bas)
- Pour tout changement dans la structure principale, communiquez et assurez-vous que vos changement ne cassent pas le code des autres
- Gardez la branche master vide sauf pour la structure principale et le EpollHandler (et ses dependances), jusqu'a ce qu'une feature soit finie
- Une branche par feature.
- On est en C++, du coup on peut s'amuser avec des classes partout et des interactions marrantes je pense. Beaucoup de wrapper, pas beaucoup de code en dur (le parsing dans une classe par exemple)

# Norme

- Noms de classe/types en CamelCase:
```
class UserList {};
```
- Noms de variables et fonctions en lowerCamelCase: (donc premier mot sans majuscule)
```
int returnValue;
```
- les noms de TOUT avec le format suivant:
  - action (get, set, start, init, flush, parse) en 1er
  - objet en toutes lettres (Command et pas cmd, Socket et pas sock...) en 2eme
  - Tout ca sans ecrire un roman, essayez d'avoir 3 mots max pour la plupart de vos fonctions. La premiere priorite c'est la clarte absolue sur ce que chaque fonction fait

```
std::pair<bool, std::string>  parseCommand(std::string data);
void                          clearSocket(Socket * socket);
```

- Pour les if, while et for, TOUJOURS utiliser un scope (meme avec une ligne).

- Les scope de tout ce qui utilise un scope sera avec le format suivant:
```
if (condition) {
  // stuff
 }
 ```
 
 - Les * et les & des pointeurs et reference seront separes des elements adjacents avec un espace:
 ```
 User * U = new User();
 ```
 
 - Des commentaires pour expliquer (au moins brievement) ce que votre fonction fait (inutile sur un constructeur par defaut ou un get/set simple)
  - Les commentaires DANS une fonction sont apprecies, mais surtout quand le code est tres technique et difficile a comprendre.
```
// Executes NICK command as per RFC 2812
bool  doNick (User * U, std::string data) {
  ...
  // returns false if nickname is already in use
  ...
}
```

- Les noms des types dans les classes ou fonctions templatees seront colles aux crochets "<>":
```
std::vector<char> charset;
```

- A part dans les prototypages de template, car on ne peut pas mettre plusieurs ">" de suite:
```
template <typename T, std::pair<bool, std::string> >
```

Tout ceci est totalement negociable, j'ai mis ce qui faisait sens pour moi. Par contre, ne passons pas 300 ans a nous mettre d'accord; si cette norme vous va, on part avec ca.
