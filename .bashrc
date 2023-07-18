alias ga="git add -A"
alias gs="git status"
alias gd="git diff"
alias gc="git commit"
alias gp="git push"
alias emacs="emacs ~/.emacs.d/init.el &"
alias lst="ls -latrh"

if [[ $(pwd) == '/' ]]; then
  cd $HOME
fi
