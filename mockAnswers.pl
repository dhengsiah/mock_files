


% child_mother(C, M) means C is a child of mother M.
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

child_mother(amy, mary).
child_mother(arthur, mary).
child_mother(angel, jane).
child_mother(anton, rita).
child_mother(alan, rita).
child_mother(axel, susan).
child_mother(ann, tina).    


% age(C, A) means C is of age A.
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

age(amy, 6).
age(arthur, 15).
age(angel, 16).
age(anton, 4).
age(alan, 8).
age(axel, 16).
age(ann, 4).

% employed(X) means X is employed.
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

employed( susan).
employed(rita).



ecb(M):-
	child_mother(C,M),
	age(C,N),
	N<15.

ecb(M):-
	child_mother(C,M),
	\+ employed(M),
	age(C,N),
	N>14,
	N<17.

mother_of_the_youngest(M):-
	age(C1,N1),
	\+ (age(C2,N2),N2 < N1),
	child_mother(C1,M).

mothers_of_young(LM):-
	setof(M,C^(child_mother(C,M),age(C,N),N=<10),LM).

merge([],[],[]).

merge(X,[],L):-
	merge([],[],L_),
	append(X,L_,L).

merge([],X,L):-
	merge([],[],L_),
	append(X,L_,L).

merge([H1|T1],[H2|T2],L):-
	H1 =< H2,
	merge(T1,[H2|T2],L_),
	append([H1],L_,L).

merge([H1|T1],[H2|T2],L):-
	H2<H1,
	merge([H1|T1],T2,L_),
	append([H2],L_,L).

findElement(1,[H|T],E):-
	E = H.

findElement(N,[H|T],E):-
	N1 is N-1,
	findElement(N1,T,E).

	
	
/*

Please ensure your predicates are spelled correctly. 
Copy and paste from the following:

ecb(M)
mother_of_the_youngest(M)
mothers_of_young(LM)

merge(L1, L2, L)
findElement(N, L, E) 

*/
