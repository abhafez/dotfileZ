# .bashrc

# If not running interactively, don't do anything
[[ $- != *i* ]] && return

alias ls='ls --color=auto'
PS1='[\u@\h \W]\$ '

source ~/.aliasrc

###########
# for ASDF
###########
. "$HOME/.asdf/asdf.sh"

. "$HOME/.asdf/completions/asdf.bash"



# Automatically start tmux
if command -v tmux &>/dev/null && [ -z "$TMUX" ]; then
	tmux attach -t default || tmux new -s default
fi
. "$HOME/.cargo/env"
