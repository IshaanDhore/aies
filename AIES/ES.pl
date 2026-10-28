
% Mini Expert System using Prolog
% Lab Assignment No. 5

:- dynamic symptom/1.

% Predefined symptoms
symptom(fever).
symptom(cough).
symptom(sore_throat).

% Knowledge base: Rules
disease(flu) :-
    symptom(fever),
    symptom(cough),
    symptom(body_pain).

disease(common_cold) :-
    symptom(cough),
    symptom(sneezing),
    symptom(runny_nose).

disease(allergy) :-
    symptom(sneezing),
    symptom(itchy_eyes).

disease(throat_infection) :-
    symptom(sore_throat),
    symptom(fever).

% Recommendations
recommendation(flu, 'Rest and consult a healthcare professional').
recommendation(common_cold, 'Rest and drink adequate fluids').
recommendation(allergy, 'Avoid allergens and seek medical advice if needed').
recommendation(throat_infection, 'Consult a healthcare professional').

% Main program
start :-
    write('Mini Expert System'), nl,
    write('Enter symptoms one by one.'), nl,
    write('Available symptoms: fever, cough, sore_throat, body_pain, sneezing, runny_nose, itchy_eyes'), nl,
    write('Type stop. when finished.'), nl,
    read_symptoms,
    nl,
    write('Expert System Results:'), nl,
    findall(Disease, disease(Disease), Diseases),
    (   Diseases = []
    ->  write('No matching condition found.'), nl
    ;   show_recommendations(Diseases)
    ),
    clear_user_symptoms.

% Read multiple symptoms
read_symptoms :-
    write('Enter symptom: '),
    read(Input),
    (   Input == stop
    ->  true
    ;   (   valid_symptom(Input)
        ->  (   symptom(Input)
            ->  true
            ;   assertz(symptom(Input))
            )
        ;   write('Unknown symptom. Try again.'), nl
        ),
        read_symptoms
    ).

% Allowed symptoms
valid_symptom(fever).
valid_symptom(cough).
valid_symptom(sore_throat).
valid_symptom(body_pain).
valid_symptom(sneezing).
valid_symptom(runny_nose).
valid_symptom(itchy_eyes).

% Display results
show_recommendations([]).
show_recommendations([Disease|Rest]) :-
    write('Possible condition: '),
    write(Disease), nl,
    (   recommendation(Disease, Advice)
    ->  write('Recommendation: '),
        write(Advice), nl
    ;   true
    ),
    show_recommendations(Rest).

% Remove only symptoms entered by the user
clear_user_symptoms :-
    retractall(symptom(body_pain)),
    retractall(symptom(sneezing)),
    retractall(symptom(runny_nose)),
    retractall(symptom(itchy_eyes)).

\\ start.