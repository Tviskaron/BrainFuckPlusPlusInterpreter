#include <iostream>

using namespace std;

const int SZ = 30000;
const int MOD = 256;

int a[SZ];
string s;
int variable = 0;
int current_ceil = 0;
int I = 0;

//-------------------------
void move_current_ceil_right() {
    current_ceil += 1;
    if (current_ceil == SZ)
        current_ceil = 0;
}

void move_current_ceil_left() {
    if (current_ceil == 0)
        current_ceil = SZ - 1;
    else
        current_ceil -=1;
}

void move_current_ceil_to_zero() {
    current_ceil = 0;
}
//-------------------------
void read_to_current_ceil() {
    cin >> a[current_ceil];
}

void write_from_current_ceil() {
    cout << a[current_ceil] << endl;
}

void apply_left_ceil() {
    move_current_ceil_left();
    int q = a[current_ceil];
    move_current_ceil_right();
    a[current_ceil] = q;
}

void apply_zero() {
    a[current_ceil] = 0;
}

void copy_current_ceil_to_variable() {
    variable = a[current_ceil];
}

void copy_variable_to_current_ceil() {
    a[current_ceil] = variable % MOD;
}

void mul_left_ceil() {
    move_current_ceil_left();
    int q = a[current_ceil];
    move_current_ceil_right();
    a[current_ceil] *= q;
    a[current_ceil] %= MOD;
}

void div_left_ceil() {
    move_current_ceil_left();
    int q = a[current_ceil];
    move_current_ceil_right();
    a[current_ceil] /= q;
    a[current_ceil] %= MOD;
}

void inc_current_ceil() {
    a[current_ceil] += 1;
    a[current_ceil] %= MOD;
}

void dec_current_ceil() {
    a[current_ceil] -= 1;
    a[current_ceil] = max(a[current_ceil], 0);
}
//-------------------------

void go(char current);

void do_loop(int loop_begin) {
    while(1) {
        if (s[I] == ']')
            I = loop_begin;

        if (s[I] == '[' && a[current_ceil] == 0) {
            while(s[I] != ']') I++;
            return;
        }
        if (s[I] == '[' && I == loop_begin){
            I++;
            continue;
        }

        go(s[I]);
        I++;
    }
}

void do_if() {
    if (!a[current_ceil])
        while(s[I] != ')') I++;
}

void print_variable() {
    cout << variable << endl;
}

void apply_variable_to_current_ceil() {
    variable = current_ceil;
}
//-------------------------


void go(char current) {
    if (current == '>')
        move_current_ceil_right();
    if (current == '<')
        move_current_ceil_left();
    if (current == '|')
        move_current_ceil_to_zero();

    if (current == ',')
        read_to_current_ceil();
    if (current == '.')
        write_from_current_ceil();
    if (current == '=')
        apply_left_ceil();
    if (current == '0')
        apply_zero();
    if (current == '!')
        copy_current_ceil_to_variable();
    if (current == '?')
        copy_variable_to_current_ceil();
    if (current == '*')
        mul_left_ceil();
    if (current == '/')
        div_left_ceil();
    if (current == '+')
        inc_current_ceil();
    if (current == '-')
        dec_current_ceil();

    if (current == '(')
        do_if();
    if (current == '[')
        do_loop(I);
    if (current == '^')
        print_variable();
    if (current == '$')
        apply_variable_to_current_ceil();
    if (current == ']')
        return;
}

int main() {
    cin >> s;
    while(I != (int)s.size()) {
        go(s[I]);
        I++;
    }
    return 0;
}
