# Mario::Edit

![Build status](https://api.travis-ci.org/CppPolska/MarioEdit.svg?branch=master)

Projekt na potrzeby wpisów z serii [SFML-owe zabawy](http://cpp-polska.pl/tag/sfmlowe%20zabawy).

Główny scenariusz do zaprogramowania:

> Otwieramy program. W menu pojawia się przycisk “Create World”. Po kliknięciu uruchamia się panel, w którym możemy przeciągać elementy gry wg zdefiniowanej siatki. Po zakończeniu etapu tworzenia świata klikamy przycisk “Play”. Umieszczamy bohatera na mapie i po naciśnięciu klawisza Enter - gramy.

## Budowanie projektu

W chwili obecnej wspierane są dwie platformy: MacOS oraz Linux. Budowanie projektu odbywa się poprzez używanie komendy `./console build`.
Jeżeli masz zastrzeżenia do systemu budowania, program nie buduje Ci się bądź chcesz pomóc w obsłudze budowania projektu na systemie Windows - daj znać.

__Uwaga Linux__

Aby zbudować projekt pod Linux'em, w systemie muszą być zainstalowane następujące biblioteki:

- libsndfile1-dev
- libxrandr-dev
- libudev-dev
- libopenal-dev
- build-essential

Po więcej szczegółów zapraszam do pliku `.travis.yml`.


## Continuous Integration

![Build status](https://api.travis-ci.org/CppPolska/MarioEdit.svg?branch=master)

Do obsługi CI podpiąłem TravisCi. Po więcej informacji zapraszam do pliku `.travis.yml`.

## Współpraca i kontakt

Jeżeli chcesz pomóc w tworzeniu projektu, bądź masz pytania do kodu, wypełnij i wyślij formularz kontaktowy na stronie: http://cpp-polska.pl/kontakt