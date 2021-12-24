./valgrind.sh

# redirections:
>test                        # doit creer test
>>test                       # doit creer test
<test                        # doit essayer d'ouvrir test
cat <a <b >c >d              # input b output d, c must be created

# pipes
ls | cat                     # affiche ls
cat | ls                     # doit afficher ls puis doit exit apres un \n
#   les redirections doivent etre faites APRES les pipes, (donc sont prioritaires par ecrasement)
cat a | < b cat | cat > c | cat # b doit etre copié dans c, rien ne doit etre ecrit dans stdout

# execution
./non_executable             # permission denied exit code 126
./directory
non_executable               # avec non_executable dans un dossier du path, permission denied
cat < directory

# exit [n]
exit -12                   # exit avec le code 244
ls fichier_qui_existe_pas; exit # exit avec le code 2
exit a                     # exit avec une erreur
exit 1 2                   # n'exit pas et renvoie un erreur
exit 1 a                   # pareil
exit a 1                   # exit avec une erreur
exit 10000                 # exit avec le code 16
exit -10000                # exit 240
exit -9223372036854775809  # exit avec une erreur

# export
export                     # affiche l'environnement trié sous la forme 'export VAR="val"' avec les characteres sensibles echappés
export VAR+=val            # concatene la variable VAR avec val

# echo
echo -nnnnnnnnn coucou     # ecrit coucou sans \n
echo -n -nnnn coucou       # pareil
echo -nnnnn -nnnna coucou  # ecrit "-nnnna coucou" sans \n

#parsing
export A="s -la" #puis faire
l$A #doit executer un ls -la (donc que le split se fait apres le remplacement de var d'env)

export A=p #puis faire
export B=w #puis faire
$A"$B"d  #doit executer un pwd, puis faire
"$A"'$B'd #ne doit pas faire de pwd car les var d'env ne sont pas remplacee dans les simple quote

echo "ls -la <a | grep x > b" #doit afficher "ls -la <a | grep x > b"
echo ok "" ok #doit avoir deux espaces car "" est un argument vide mais est un argument
echo ok "" "" "" "" "" "" "" "" "" ok #pour mieux voir ce qui est avant

export OK="ok                   ok" #puis faire
echo $OK #doit afficher "ok ok" (un seul espace entre les deux

# si il y a le ; qui est fait
unset A #pour etre sur que la variable d'environnement existe pas puis faire la suite sur une autre ligne de commande
export A=ok; echo $A  #doit afficher un ok

export A=1 B=2 C=3 D=4 E=5 F=6 G=7 H=8
echo "$A'$B"'$C"$D'$E'"$F"'"'$G'$H" #doit afficher 1'2$C"$D5"$F"'7'8
