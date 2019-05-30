#!/usr/bin/env python
# -*- coding: utf-8 -*-

# This script translates the CPU supported assembly instructions to binary instructions
# Input file may contain comments using "//", all comments will be omitted during translation
# To run: python read_instructions.py [input file] > [output file]

from __future__ import print_function
import sys

labels = {

}

branch_cond = {
    'EQ':  0b0000,
    'NE':  0b0001,
    'CS':  0b0010,
    'CC':  0b0011,
    'MI':  0b0100,
    'PL':  0b0101,
    'VS':  0b0110,
    'VC':  0b0111,
    'HI':  0b1000,
    'LS':  0b1001,
    'GE':  0b1010,
    'LT':  0b1011,
    'GT':  0b1100,
    'LE':  0b1101,
    'AL':  0b1110
}

def make_mask(size):
    n = 1
    for _ in range(size - 1):
        n <<= 1
        n += 1
    return n

def isinteger(string):
    if (string.startswith('-') and string[1:].isdigit()) or string.isdigit():
        return True
    return False

def int_to_bin(integer, pad=3):
    if type(integer) is str:
        # negatives
        if isinteger(integer):
            integer = int(integer)
        else:
            raise Exception('expected integer, instead got: {0}'.format(integer))

    if integer < 0:
        integer = integer & make_mask(pad)

    r = []
    for c in reversed(bin(integer)[2:]):
        r.append(int(c))
    r += (pad - len(r)) * [0]

    if len(r) > pad:
        raise Exception('expected an integer of bit size {2}, got {0}={1}'.format(integer, bin(integer), pad))
    return r

#imm3 8..6
def set_imm3(integer, out16):
    out16[6:9] = int_to_bin(integer)

#imm6 10..6
def set_imm5(integer, out16):
    out16[6:11] = int_to_bin(integer, 5)

#imm6 5..0
def set_imm6(integer, out16):
    out16[0:6] = int_to_bin(integer, 6)

#imm7 6..0
def set_imm7(integer, out16):
    out16[0:7] = int_to_bin(integer, 7)

#imm8 7..0
def set_imm8(integer, out16):
    out16[0:8] = int_to_bin(integer, 8)

#imm11 10..0
def set_imm11(integer, out16):
    out16[0:11] = int_to_bin(integer, 11)


def validate_register(string, bit_length=3):
    if string[0] != 'R':
        raise Exception('expecting register in form of RN, ie: R3 etc. got: {0}'.format(string))
    elif not string[1:].isdigit():
        raise Exception('expecting integer for register in form of RN, ie: R3 etc. got: {0}'.format(string))
    value = int(string[1:])
    if len(bin(value)[2:]) > bit_length:
        raise Exception('register integer value exceeds bit length={0} for the instruction, got: {1}={2}'.format(bit_length, string, bin(value)))

    return value


#rm 8..6
def set_rm(register, out16):
    out16[6:9] = int_to_bin(validate_register(register))

#rm 6..3
def set_rm_mov(register, out16):
    if register == 'LR':
        register = 'R14' #update aliased register value
    out16[3:7] = int_to_bin(validate_register(register, 4), 4)

#rn/rm 5..3
def set_rn(register, out16):
    out16[3:6] = int_to_bin(validate_register(register))

#rd/rdn/rn 2..0
def set_rd(register, out16):
    out16[0:3] = int_to_bin(validate_register(register))

#rd/rdn/rn 10..8
def set_rd_mov(register, out16):
    out16[8:11] = int_to_bin(validate_register(register))

#cond 11..8
def set_cond(integer, out16):
    out16[8:12] = int_to_bin(integer, 4)

#
# instruction handling
#

out16 = []

def add_label(label, index):
    if label in labels:
        raise Exception('label already exists, duplicates are not allowed: {0}'.format(label))
    labels[label] = index

def get_label_index(label, index):
    if label not in labels:
        raise Exception('label does not exist: {0}'.format(label))
    return labels[label] - index

def read_instruction(string):
    global instruction_index
    # print('instruction: {}'.format(string))

    split = string.upper().split()
    instruction = split[0]

    # label
    if instruction[-1] == ':':
        label = split.pop(0)
        instruction = split[0]

    out16 = 16 * [0]

    # MOVS Rd, #<imm>
    if instruction == 'MOVS':
        rd = split[1].strip(',')
        imm8 = split[2]

        set_rd_mov(rd, out16)
        set_imm8(imm8, out16)

        out16[11:16] = int_to_bin(0b00100, 5)
    # MOV Rd, Rm
    elif instruction == 'MOV':
        rd = split[1].strip(',')
        rm = split[2]

        set_rd(rd, out16)
        set_rm_mov(rm, out16)

        out16[7:16] = int_to_bin(0b010001100, 9)
    elif instruction == 'ADD':
        # ADD SP, SP, #<imm7>
        make_imm7_instruction(0b101100000, out16, split, string)
    elif instruction == 'ADDS':
        # ADDS Rd, Rn, #<imm3>
        if split[3][0].isdigit():
            rd = split[1].strip(',')
            rn = split[2].strip(',')
            imm3 = split[3]

            set_rd(rd, out16)
            set_rn(rn, out16)
            set_imm3(imm3, out16)

            out16[9:16] = int_to_bin(0b0001110, 7)
        # ADDS Rd, Rn, Rm
        else:
            rd = split[1].strip(',')
            rn = split[2].strip(',')
            rm = split[3]

            set_rd(rd, out16)
            set_rn(rn, out16)
            set_rm(rm, out16)

            out16[9:16] = int_to_bin(0b0001100, 7)
    elif instruction == 'SUB':
        # SUB SP, SP, #<imm7>
        make_imm7_instruction(0b101100001, out16, split, string)
    elif instruction == 'SUBS':
        # SUBS Rd, Rn, Rm
        if not split[3][0].isdigit():
            rd = split[1].strip(',')
            rn = split[2].strip(',')
            rm = split[3]

            set_rd(rd, out16)
            set_rn(rn, out16)
            set_rm(rm, out16)

            out16[9:16] = int_to_bin(0b0001101, 7)
        # SUBS Rd, Rn, #<imm3>
        else:
            rd = split[1].strip(',')
            rn = split[2].strip(',')
            imm3 = split[3]

            set_rd(rd, out16)
            set_rn(rn, out16)
            set_imm3(imm3, out16)

            out16[9:16] = int_to_bin(0b0001111, 7)
    # CMP Rn, Rm (Encoding 1)
    elif instruction == 'CMP':
        rn = split[1].strip(',')
        rm = split[2]

        set_rd(rn, out16) # this is correct, dont change
        set_rn(rm, out16) # this is correct, dont change

        out16[6:16] = int_to_bin(0b0100001010, 10)
    # ANDS Rdn, Rm
    elif instruction == 'ANDS':
        make_rdnrm_instruction(0b0100000000, out16, split, string)
    # EORS Rdn, Rm
    elif instruction == 'EORS':
        make_rdnrm_instruction(0b0100000001, out16, split, string)
    # ORRS Rdn, Rm
    elif instruction == 'ORRS':
        make_rdnrm_instruction(0b0100001100, out16, split, string)
    # MVNS Rdn, Rm
    elif instruction == 'MVNS':
        make_rdnrm_instruction(0b0100001111, out16, split, string)
    # LSLS Rd, Rd, Rm
    elif instruction == 'LSLS':
        make_rdrnrm_instruction(0b0100000010, out16, split, string)
    # LSRS Rd, Rd, Rm
    elif instruction == 'LSRS':
        make_rdrnrm_instruction(0b0100000011, out16, split, string)
    # ASRS Rd, Rd, Rm
    elif instruction == 'ASRS':
        make_rdrnrm_instruction(0b0100000100, out16, split, string)
    # RORS Rd, Rd, Rm
    elif instruction == 'RORS':
        make_rdrnrm_instruction(0b0100000111, out16, split, string)
    # MULU Rd, Rd, Rm
    elif instruction == 'MULU':
        make_rdrnrm_instruction(0b0100000101, out16, split, string)
    # DIVU Rd, Rd, Rm
    elif instruction == 'DIVU':
        make_rdrnrm_instruction(0b0100000110, out16, split, string)
    # STR Rd, [Rn, #<imm5>]
    elif instruction == 'STR':
        make_imm5_instruction(0b01100, out16, split, string)
    # LDR Rd, [Rn, #<imm5>]
    elif instruction == 'LDR':
        make_imm5_instruction(0b01101, out16, split, string)
    # B <label>
    elif instruction == 'B':
        label = split[1]

        set_imm11(get_label_index(label, instruction_index), out16)

        out16[11:16] = int_to_bin(0b11100, 5)
    # BL <label>
    elif instruction == 'BL':
        label = split[1]

        set_imm6(get_label_index(label, instruction_index), out16)

        out16[6:16] = int_to_bin(0b0100010100, 10)
    # BX Rm
    elif instruction == 'BX':
        rm = split[1]

        set_rm_mov(rm, out16)

        out16[7:16] = int_to_bin(0b010001110, 9)
    # B<cc> <label>
    elif instruction[0] == 'B':
        branch_type = instruction[1:]
        if branch_type not in branch_cond:
            raise Exception('invalid branch type detected: {0}'.format(instruction))
        cond = branch_cond[branch_type]
        label = split[1]

        set_cond(cond, out16)
        set_imm8(get_label_index(label, instruction_index), out16)

        out16[12:16] = int_to_bin(0b1101, 4)
    elif instruction == 'NOOP':
        out16 = int_to_bin(0b1011111100000000, 16)
    else:
        raise Exception('invalid instruction: {0}'.format(instruction))
    instruction_index += 1
    return list(reversed(out16))

# ADD SP, SP, #<imm7>
def make_imm7_instruction(instruction_code, out16, split, string):
    sp = split[1].strip(',')
    sp2 = split[2].strip(',')
    imm7 = split[3]
    if sp != 'SP' and sp != sp2:
        raise Exception('expecting {0} SP, SP, <integer>, got: {1}'.format(instruction,string))

    set_imm7(imm7, out16)

    out16[7:16] = int_to_bin(instruction_code, 9)
# <x> Rdn, Rm
def make_rdnrm_instruction(instruction_code, out16, split, string):
    rdn = split[1].strip(',')
    rm = split[2]

    set_rd(rdn, out16) # this is correct, dont change
    set_rn(rm, out16) # this is correct, dont change

    out16[6:16] = int_to_bin(instruction_code, 10)

# <x> Rd, Rd, Rm
def make_rdrnrm_instruction(instruction_code, out16, split, string):
    rd = split[1].strip(',')
    rd2 = split[2].strip(',')
    if rd != rd2:
        raise Exception('second register does not equal first: {0}'.format(string))
    rm = split[3]

    set_rd(rd, out16) # this is correct, dont change
    set_rn(rm, out16) # this is correct, dont change

    out16[6:16] = int_to_bin(instruction_code, 10)

# <x> Rd, [Rn, #<imm5>]
def make_imm5_instruction(instruction_code, out16, split, string):
    rd = split[1].strip(',')
    rn = split[2].strip('[,')
    imm5 = split[3].strip(']')

    set_rd(rd, out16) # this is correct, dont change
    set_rn(rn, out16) # this is correct, dont change
    set_imm5(imm5, out16)

    out16[11:16] = int_to_bin(instruction_code, 5)

#
# main execution
#

instruction_index = 0
line_index = 1

def collect_labels(string, instruction_index):
    param = string.split()
    param = param[0]
    if param[-1] == ':':
        label = param[:-1]
        add_label(label, instruction_index)

def fetch_instructions(file_data):
    global line_index

    for line in file_data:
        line_index += 1
        line = line.strip()
        if len(line) > 0 and line[0:2] != '//':
            # remove comments
            line = line.split('//')[0].strip()
            yield line

def main(filename):
    global instruction_index, line_index

    try:
        f = open(filename)
        file_data = f.readlines()
        f.close()
    except Exception:
        print('error attempting to open file "{0}", it may not exist'.format(filename), file=sys.stderr)
        return

    # grab all of the labels
    for line in fetch_instructions(file_data):
        try:
            collect_labels(line, instruction_index)
        except Exception as e:
            print('error getting labels on line {0}: {1}'.format(line_index, e[0]), file=sys.stderr)
            return
        instruction_index += 1

    instruction_index = 0

    results = []

    line_index = 1

    for line in fetch_instructions(file_data):
        try:
            results.append('{0} {1}'.format('//', line)) #print the assembly code as a comment
            results.append(''.join([str(x) for x in read_instruction(line)]))
        except Exception as e:
            print('error on line {0}: {1}'.format(line_index, e[0]), file=sys.stderr)
            return

    for line in results:
        print(line)

def validate_args(args):
    if len(args) != 2:
        print('error: this program takes one argument as input: FILENAME\n\
            To save binary tranlation to a file use: read_instructions.py [input file] > [output file]\n', file=sys.stderr)
        return None
    return args[1]

if __name__ == '__main__':
    filename = validate_args(sys.argv)

    if type(filename) is str:
        main(filename)
