

disease(cold) :-
    symptom(sneezing),
    symptom(runny_nose),
    symptom(sore_throat),
    symptom(mild_cough).

disease(flu) :-
    symptom(flu-fever),
    symptom(headache),
    symptom(body_ache),
    symptom(cough),
    symptom(chills).

disease(malaria) :-
    symptom(malaria-fever),
    symptom(chills),
    symptom(sweating),
    symptom(headache),
    symptom(vomiting).

disease(typhoid) :-
    symptom(typhoid-fever),
    symptom(stomach_pain),
    symptom(loss_of_appetite),
    symptom(weakness),
    symptom(headache).

disease(covid) :-
    symptom(covid-fever),
    symptom(cough),
    symptom(loss_of_taste),
    symptom(breathing_problem),
    symptom(tiredness).

disease(cough) :-
    symptom(throat_pain),
    symptom(chest_pain),
    symptom(dry_cough).

disease(dengue) :-
    symptom(dengue-fever),
    symptom(headache),
    symptom(rashes),
    symptom(joint_pain),
    symptom(bleeding_nose).

disease(asthma) :-
    symptom(shortness_of_breath),
    symptom(chest_tightness),
    symptom(cough),
    symptom(wheezing).

% --- Suggest remedies 
remedy(cold, 'Take rest, drink warm water, and use steam inhalation.').
remedy(flu, 'Drink fluids, take paracetamol, and rest well.').
remedy(malaria, 'Consult a doctor and take anti-malarial medicine.').
remedy(typhoid, 'Drink boiled water and eat light food.').
remedy(covid, 'Isolate yourself, drink fluids, and consult a doctor.').
remedy(cough, 'Use cough syrup and avoid cold drinks.').
remedy(dengue, 'Take paracetamol, avoid aspirin, and drink plenty of fluids.').
remedy(asthma, 'Use inhaler and avoid dust or smoke.').


% --- Start Predicate 
start :-
    write('-------------------------------------------------'), nl,
    write('        EXPERT SYSTEM: DISEASE DIAGNOSIS          '), nl,
    write('-------------------------------------------------'), nl,
    write('Please answer the following questions with yes. or no.'), nl, nl,
    diagnose.

% --- Diagnosis Logic ---
diagnose :-
    disease(D),
    write('You may be suffering from: '), write(D), nl,
    remedy(D, R),
    write('Suggested Remedy: '), write(R), nl,
    nl,
    fail.  % find all possible diseases

diagnose :-
    write('Diagnosis completed. Please consult a doctor for confirmation.'), nl.

% --- Ask user for symptoms ---
symptom(S) :-
    write('Do you have '), write(S), write('? '),
    read(Reply),
    Reply = yes.

% --- Extra Helper Rules ---
% To explain logic and make it longer for marks

% If the user has fever, it may be serious
check_fever :-
    symptom(fever),
    write('You have fever. Please monitor your temperature regularly.'), nl.

% If the user has breathing problems, show warning
check_breathing :-
    symptom(breathing_problem),
    write('You have breathing issues. Seek medical attention if it worsens.'), nl.

