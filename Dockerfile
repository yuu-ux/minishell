FROM --platform=linux/x86_64 ubuntu:20.04


RUN apt update && apt install -y make git gcc curl tmux zsh bear

COPY . /minishell

SHELL ["/bin/zsh", "-c"]

# コンテナのエントリーポイント
RUN git clone https://github.com/yuu-ux/dotfiles && cd dotfiles && chmod +x setting.sh && ./setting.sh && git clone https://github.com/asdf-vm/asdf.git ~/.asdf --branch v0.14.1 && source ~/.zshrc && asdf plugin add neovim && asdf install neovim 0.10.0 && asdf global neovim 0.10.0


WORKDIR /minishell

CMD ["/bin/zsh"]
