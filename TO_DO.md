# TO DO:

## Connect 4:
  - Mode: Multi 4-like combinations. Who makes more, win

## Simon: 
  *. ["Specs" Page](http://www.autobahn.com.br/brinquedos/genius.html)
  - Skill levels (sequence limit)
    - Level 1: 8
    - Level 2: 14
    - Level 3: 20
    - Level 4: 31
  - Modes:
    - Mode 1: Classic genius challeng (alredy done)
    - Mode 2: You make your own sequence and repeat it
    - Mode 3: Classic challenge, but removing the mistaken color from future sequences
  - Timer:
    - The max time to input a input is 5 seconds
    
    
## Battleship:
  - Map parser
    - It'll detect ships and its type
    - Must enforce the rules
    - Make rule deactivation easy (in code)
  - Ship types and quantity
    - 5 Hydroplanes
    - 4 Submarines
    - 3 Cruiser
    - 2 Battleship
    - 1 Aircraft Carrier
  - The ships shouldn't touch each other, one square of space between at least
  - Map size: 15 x 15
  - ### Easy Rule:
  
    1. Disparará 3 tiros, indicando a coordenadas do alvo através do número da linha e da letra da coluna que definem a posição. Para que o jogador tenha o controle dos tiros disparados, deverá marcar cada um deles no reticulado intitulado "Seu jogo".

    2. Após cada um dos tiros, o oponente avisará se acertou e, nesse caso, qual a arma foi atingida. Se ela for afundada, esse fato também deverá ser informado.

    3. A cada tiro acertado em um alvo, o oponente deverá marcar em seu tabuleiro para que possa informar quando a arma for afundada.

    4. Uma arma é afundada quando todas as casas que formam essa arma forem atingidas.

    5. Após os 3 tiros e as respostas do opoente, a vez para para o outro jogador.
    
  - ### Hard Rule:
    1. Disparará 3 tiros consecutivos, indicando a coordenadas do alvo através do número da linha e da letra da coluna que definem a posição. Para que o jogador tenha o controle dos tiros disparados, deverá marcar cada um deles no reticulado intitulado "Seu jogo".

    2. Após os 3 tiros, o oponente avisará quantos acertaram, mas não quais, informando também quais as armas foram atingidas. Se uma delas for totalmente destruída, esse fato também deverá ser informado.

    3. A cada tiro acertado em um alvo, o oponente deverá marcar em seu tabuleiro para que possa informar quando a arma for destruída.

    4. Uma arma é afundada quando todas as casas que formam essa arma forem atingidas.

    5. Após os 3 tiros e a resposta do opoente, a vez para para o outro jogador.

