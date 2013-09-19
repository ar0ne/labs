:- dynamic(progress/2).

main :-
  intro,
  reset_answers,
  find_solution(Solution),
  describe(Solution), nl.

intro :-
    write('У вас сегодня экзамен, а вы проснулись слишком поздно'), nl,
    write('Вам естественно, надо успеть на него, но'), nl,
    write('Как? Мы постараемся дать вам совет, исходя из сложившейся ситуации '), nl,
    write('Вам поступить, но для этого вы должны предоставить всю информацию, '), nl,
    write('Итак начнем...'), nl.

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

find_solution(Solution) :-
    solution(Solution), !.

% Rules for the knowledge base
solution(do_nothing) :-
    are_you_really_late(no).
solution(take_taxi) :-
    big_late,
    main_exam.
solution(take_taxi_partially) :-
    \+ big_late,
    main_exam.
solution(take_common_transport) :-
    \+ main_exam.
solution(can_not_help) :-
    !.

describe(do_nothing) :-
    write('Все в порядке, желаю вам ни пуха.'), nl.
describe(take_taxi) :- 
    write('Берите такси на весь путь до института! В такой ситуации деньги не важны'), nl.
describe(take_common_transport) :- 
    write('Успокойтесь, на не очень важный экзамен не стоит сильно спешить. Поверьте вам простят ваше опаздание'),
    write(' или даже отсутсвие. Так что неспеша поезжайте на общественном транспорте'), nl.
describe(take_taxi_partially) :-
    write('Не волнуйтесь, все еще будет хорошо. Вам стоит взять такси на часть пути. Например, до какого-нибудь'),
    write(' узлового пункта (до метро, авт., остановки'), nl.
describe(can_not_help) :-
    write('Не могу ничего подсказать...'), nl.

answer(yes) :-
    write('Yes').
answer(no) :-
    write('No').

question(are_you_really_late) :-
    write('Скажите, вы действительно опаздываете'), nl.
question(how_long_on_common):-
    write('Сколько минут вам добираться до института на общественном транспорте'), nl.
question(how_long_on_walk):-
    write('Сколько минут вам приходится идти пешком'), nl.
question(how_long_by_metro):-
    write('Сколько минут вам приходится проводить в метро'), nl.
question(how_long_by_bus):-
    write('Сколько минут вам приходится проводить в автобусе'), nl.
question(only_good_marks) :-
    write('На предстоящем экзамене ставят только 4 и выше'), nl.
question(what_veroyatn) :-
    write('Какова объективная вероятность получения вами желаемой оценки'), nl.

are_you_really_late(Answer) :-
    progress(are_you_really_late, Answer).
are_you_really_late(Answer) :-
    \+ progress(are_you_really_late, _),
    ask(are_you_really_late, Answer, [yes, no]).

only_good_marks(Answer) :-
    progress(only_good_marks, Answer).
only_good_marks(Answer) :-
    \+ progress(only_good_marks, _),
    ask(only_good_marks, Answer, [yes, no]).

big_late :- 
    asked_about_time,
    is_late.
big_late :- 
    \+ asked_about_time,
    ask(how_long_on_common),
    ask(how_long_on_walk),
    ask(how_long_by_metro),
    ask(how_long_by_bus),
    is_late.

asked_about_time :-
    progress(how_long_on_common, _),
    progress(how_long_on_walk, _),
    progress(how_long_by_metro, _),
    progress(how_long_by_bus, _).

is_late :-
    progress(how_long_on_common, Common),
    progress(how_long_on_walk, OnWalk),
    progress(how_long_by_metro, ByMetro),
    progress(how_long_by_bus, ByBus),
    % format('~w, ~w, ~w, ~w', [Common, OnWalk, ByMetro, ByBus]), nl,
    Common < OnWalk + ByMetro + ByBus + 15.

is_small_chance :-
    progress(what_veroyatn, Veroyatn),
    Veroyatn < 90.

small_chance :-
    progress(what_veroyatn, _).
small_chance :-
    \+ progress(what_veroyatn, _),
    ask(what_veroyatn),
    is_small_chance.

main_exam :-
    only_good_marks(no).    
main_exam :-
    small_chance.
main_exam :-
    small_chance,
    only_good_marks(no).

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

reset_answers :-
  retract(progress(_, _)),
  fail.
reset_answers.

 answers([], _).
 answers([First|Rest], Index) :-
  write(Index), write(' '), answer(First), nl,
  NextIndex is Index + 1,
  answers(Rest, NextIndex).

parse(0, [First|_], First).
parse(Index, [First|Rest], Response) :-
  Index > 0,
  NextIndex is Index - 1,
  parse(NextIndex, Rest, Response).

ask(Question, Answer, Choices) :-
  question(Question),
  answers(Choices, 0),
  read(Index),
  parse(Index, Choices, Response),
  asserta(progress(Question, Response)),
  Response = Answer.

ask(Question) :-
  question(Question),
  read(Response),
  asserta(progress(Question, Response)).

