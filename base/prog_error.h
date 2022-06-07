#pragma once
enum progError
{
    k_UNEXPECTED_TERMINATION_OF_STRING, // A NEW LINE BEFORE SECOND '
    k_UNEXPECTED_TERMINATION_OF_OPERATOR, // ABSENCE OF ; OR UNEXPECTED TRANSITION TO A NEW LINE
    k_ENDLESS_ONE_LINE_COMMENT, // ABSENCE OF } IN COMMENT OR A NEW LINE. COMMENTS ARE ONLY SINGLE-LINE
    k_INCORRECT_TABULATION, // NOT A MULTIPLE OF THE SPECIFIED NUMBER OF SPACES
    k_INCORRECT_NESTING_LEVEL,// TOO MANY OR TOO FEW TABS
    k_TOO_MANY_ARGUMENTS, // IT CAN BE IN WRITE, READ OPERATORS. MAY BE MORE
    k_FIRST_PART_OF_PAIR_IS_MISSED, // ] OR ) OR } BEFORE [ OR ) OR }
    k_NO_PROGRAM_KEY_WORD, //THERE IS NO WORD PROGRAM AT THE BEGINNING
    k_NO_PROGRAM_NAME, // THERE IS NO NAME OF PROGRAM IN FIRST LINE
    k_CUT_DOUBLE_VALUE, // BEGINS FROM POINT. MUST BEGIN FROM DIGIT
    k_ID_NO_DECLARATED,
    k_CONST_NOT_INIT,
    k_CHANGED_CONST_VALUE,
    k_INCORRECT_OPERATION,
    k_INCORRECT_WRITE_CALL,
    k_ID_DOUBLE_DECLARATION,

    k_UNDEFINED_ERROR // DO NOT USE IT! 

};