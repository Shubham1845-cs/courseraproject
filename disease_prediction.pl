% --- Disease Prediction Expert System (SWISH version) ---
:- dynamic symptom/1.    % <--- required to assert/retract symptom/1 at runtime

% --- Disease rules ---
disease(flu) :-
    symptom(fever),
    symptom(headache),
    symptom(runny_nose),
    symptom(cough).

disease(cold) :-
    symptom(sneezing),
    symptom(runny_nose),
    symptom(sore_throat).

disease(malaria) :-
    symptom(fever),
    symptom(chills),
    symptom(sweating),
    symptom(headache).

disease(typhoid) :-
    symptom(fever),
    symptom(abdominal_pain),
    symptom(fatigue),
    symptom(loss_of_appetite).

disease(covid19) :-
    symptom(fever),
    symptom(cough),
    symptom(loss_of_smell),
    symptom(shortness_of_breath).

% --- Simulated responses (for SWISH demo) ---
response(fever, yes).
response(headache, yes).
response(runny_nose, yes).
response(cough, yes).
response(sneezing, no).
response(sore_throat, no).
response(chills, no).
response(sweating, no).
response(abdominal_pain, no).
response(fatigue, no).
response(loss_of_appetite, no).
response(loss_of_smell, no).
response(shortness_of_breath, no).

% --- Ask rule (no actual input; uses simulated responses) ---
ask(Symptom) :-
    response(Symptom, Ans),
    format('Do you have ~w? (simulated: ~w)~n', [Symptom, Ans]),
    (Ans == yes -> assertz(symptom(Symptom)); true).

% --- Clear previous facts ---
clear_symptoms :- retractall(symptom(_)).

% --- Start diagnosis ---
start :-
    clear_symptoms,
    write('--- Disease Prediction Expert System ---'), nl,
    write('Simulated diagnosis (no user input needed)'), nl,
    nl, write('Checking symptoms...'), nl,

    ask(fever), ask(headache), ask(runny_nose), ask(cough),
    ask(sneezing), ask(sore_throat), ask(chills), ask(sweating),
    ask(abdominal_pain), ask(fatigue), ask(loss_of_appetite),
    ask(loss_of_smell), ask(shortness_of_breath),

    (   disease(D) ->
        nl, write('You might be suffering from: '), write(D), nl
    ;   nl, write('Sorry, no matching disease found.'), nl
    ).
