# Projeto de IP

Projeto de Introdução à Programação - CIn, UFPE.  
De maneira geral, o projeto é um jogo que envolve conexão entre pessoas em computadores diferentes jogando ao mesmo tempo.  
Para isso, vai ser usada a arquitetura cliente-servidor, e a ferramenta utilizada na conexão é socket.
Neste git será disponibilizada uma biblioteca desenvolvida pela equipe de monitores, para facilitar o uso de socket.  

## O que é?

Como dito anteriormente, o projeto vai se basear na arquitetura cliente-servidor então nada mais normal que a biblioteca separe bem as funções do cliente e as do servidor. Ela conta com um header para os clientes (client.h) e para o servidor (server.h).

## Documentação
A documentação das duas bibliotecas podem ser encotradas em:

- [server.h](./server-doc.md)
- [client.h](./client-doc.md)


## Compilando e rodando:

No arquivo do [makefile](./makefile) as variáves _serverName_ e _clientName_ devem ser substituidas para o nome do arquivo do código do servidor e cliente que deseja compilar e/ou executar.  
#### Compilando e rodando o server:
	$ make server
#### Compiando e rodando o client:
	$ make client
#### Compilando client e server:
	$ make


## Exemplos:
Idealmente alguns exemplos de uso da biblioteca serão colocados na pasta de exemplos.
* [Simple Chat](./examples/simpleChatExplanation.md)


## Agradecimentos:
Esta é uma modificação de 2019.2, onde [Flavio Júnior](https://github.com/FlaviojunioR-JCV), [Antonio Carlos](https://github.com/AntonidasReborn), [Renan Siqueira](https://github.com/Renangsa) , [Vinicius Principe](https://github.com/ViniciusPrincipe) , [Heitor](https://github.com/Hbprado) , [Vinicius Pereira](https://github.com/vinipa) e [João Barreto](https://github.com/joaopbarret) foram contribuidores.
