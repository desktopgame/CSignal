#ifndef BEACON_VM_GENERATE_H
#define BEACON_VM_GENERATE_H
#include "opcode_buf.h"
#include "../env/field.h"
#include "../env/method.h"
#include "../env/property.h"

/**
 * �t�B�[���h���擾����R�[�h�𐶐����܂�.
 * @param buf
 * @param fi
 * @param index
 */
void generate_get_field(opcode_buf* buf, field* fi, int index);

/**
 * �v���p�e�B���擾����R�[�h�𐶐����܂�.
 * @param buf
 * @param prop
 * @param index
 */
void generate_get_property(opcode_buf* buf, property* prop, int index);

/**
 * �t�B�[���h�ɑ������R�[�h�𐶐����܂�.
 * @param buf
 * @param fi
 * @param index
 */
void generate_put_field(opcode_buf* buf, field* fi, int index);
/**
 * �v���p�e�B�ɑ������R�[�h�𐶐����܂�.
 * @param buf
 * @param fi
 * @param index
 */
void generate_put_property(opcode_buf* buf, property* prop, int index);
#endif