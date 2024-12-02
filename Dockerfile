# syntax=docker/dockerfile:1

FROM --platform=linux/x86_64 ubuntu:20.04

RUN apt update && apt install -y make git gcc curl tmux zsh bear libreadline-dev man-db python3 python3-venv ripgrep

RUN curl -LsSf https://astral.sh/uv/install.sh | sh

RUN uv tool install norminette@3.3.51 \
    uv tool install c-formatter-42

SHELL ["/bin/zsh", "-c"]

ENV SHELL=/bin/zsh

RUN git clone https://github.com/yuu-ux/dotfiles /root/dotfiles \
    && cd /root/dotfiles && chmod +x setting.sh && ./setting.sh

RUN git clone https://github.com/asdf-vm/asdf.git ~/.asdf --branch v0.14.1 && source ~/.zshrc \
    && asdf plugin add neovim && asdf install neovim 0.10.0 && asdf global neovim 0.10.0

RUN yes | unminimize

WORKDIR /root

CMD ["/bin/zsh"]
