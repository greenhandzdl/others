% swipl
% consult('family.pl').
% 或简写为 [family].
% father(john, lisa).   
% halt

% build
% swipl -s family.pl -g "parent(X, bob), writeln(X), fail."
% qsave_program('family.exe', [goal=grandfather(john, lisa)]).


% 定义事实（家庭成员关系）
father(john, lisa).
father(john, bob).
mother(mary, lisa).
mother(mary, bob).

% 定义规则（父子/母子关系）
parent(X, Y) :- father(X, Y).
parent(X, Y) :- mother(X, Y).

% 查询祖父关系（示例规则）
grandfather(X, Z) :- father(X, Y), parent(Y, Z).