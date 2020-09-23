// cesun, 9/22/20 6:17 PM.

// https://stackoverflow.com/a/33333636/8311608
// precondition: input>0 && ceil>0
int fast_mod(const int input, const int ceil) {
    return input >= ceil ? input % ceil : input;
}
