# mse (Minimal Simple Editor)

focado em levesa e simplicidade escrito em C utilizando a biblioteca Ncurses

para utilizar deste programa e necessario instalar os items abaixo no seu sistema Linux:
- gcc
- make
- libncurses-dev
## instalacao e uso
```bash
git clone https://github.com/laclaveme80/mse.git
cd mse
make
sudo make install
mse README.md
```
## para desintalacao
```bash
sudo make uninstall
```
## comandos

- ctrl + q, sair do editor
- ctrl + s, salvar o arquivo

## configuracao

e feita modificando o arquivo config.h e compilando
