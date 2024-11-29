#include <addresses.h>
#include <bitbuf.h>
#include <messages.h>
#include <versions.h>

class c_user_cmd {
public:
    c_user_cmd() { memset(this, 0, sizeof(*this)); }
    virtual ~c_user_cmd() {}

    int command_number;
    int tickcount;

    float viewangles[3];
    float aimdirection[3];

    float forwardmove;
    float sidemove;
    float upmove;

    int buttons;
    char impulse;

    int weaponselect;
    int weaponsubtype;
    int random_seed;

    short mousedx;
    short mousedy;

    bool predicted;

    float headangles[3];
    float headoffset[3];
};

__forceinline void read_user_cmd(c_bit_read* a1, c_user_cmd* a2, c_user_cmd* a3) {
    *a2 = *a3;

    if (a1->read_bit())
        a2->command_number = a1->read_ubit_long(32);
    else
        a2->command_number = a3->command_number + 1;

    if (a1->read_bit())
        a2->tickcount = a1->read_ubit_long(32);
    else
        a2->tickcount = a3->tickcount + 1;

    if (a1->read_bit())
        a2->viewangles[0] = a1->read_float();

    if (a1->read_bit())
        a2->viewangles[1] = a1->read_float();

    if (a1->read_bit())
        a2->viewangles[2] = a1->read_float();

    if (a1->read_bit())
        a2->aimdirection[0] = a1->read_float();

    if (a1->read_bit())
        a2->aimdirection[1] = a1->read_float();

    if (a1->read_bit())
        a2->aimdirection[2] = a1->read_float();

    if (a1->read_bit())
        a2->forwardmove = a1->read_float();

    if (a1->read_bit())
        a2->sidemove = a1->read_float();

    if (a1->read_bit())
        a2->upmove = a1->read_float();

    if (a1->read_bit())
        a2->buttons = a1->read_ubit_long(32);

    if (a1->read_bit())
        a2->impulse = a1->read_ubit_long(8);

    if (a1->read_bit()) {
        a2->weaponselect = a1->read_ubit_long(11);
            
        if (a1->read_bit())
            a2->weaponsubtype = a1->read_ubit_long(6);
    }

    // not important (?)
    a2->random_seed = (a2->command_number * 0xDEADEAD) & 0x7FFFFFFF;

    if (a1->read_bit())
        a2->mousedx = a1->read_sbit_long(16);

    if (a1->read_bit())
        a2->mousedy = a1->read_sbit_long(16);

    if (a1->read_bit())
        a2->headangles[0] = a1->read_float();

    if (a1->read_bit())
        a2->headangles[1] = a1->read_float();

    if (a1->read_bit())
        a2->headangles[2] = a1->read_float();

    if (a1->read_bit())
        a2->headoffset[0] = a1->read_float();
}

__forceinline bool write_delta_int(c_bf_write* buf, int from, int to, int bits = 32) {
	if (from == to) {
		buf->write_bit(0);
		return 0;
	}

	buf->write_bit(1);
	buf->write_ubit_long(to, bits);

	return 1;
}

__forceinline bool write_delta_float(c_bf_write* buf, float from, float to) {
	if (from == to) {
		buf->write_bit(0);
		return 0;
	}

	buf->write_bit(1);
	buf->write_float(to);

	return 1;
}

__forceinline bool write_delta_short(c_bf_write* buf, int from, int to) {
	if (from == to) {
		buf->write_bit(0);
		return 0;
	}

	buf->write_bit(1);
	buf->write_short(to);

	return 1;
}

__forceinline void write_user_cmd(c_bf_write* buf, c_user_cmd* to, c_user_cmd* from) {
	write_delta_int(buf, from->command_number + 1, to->command_number, 32);
	write_delta_int(buf, from->tickcount + 1, to->tickcount, 32);

	write_delta_float(buf, from->viewangles[0], to->viewangles[0]);
	write_delta_float(buf, from->viewangles[1], to->viewangles[1]);
	write_delta_float(buf, from->viewangles[2], to->viewangles[2]);

	write_delta_float(buf, from->aimdirection[0], to->aimdirection[0]);
	write_delta_float(buf, from->aimdirection[1], to->aimdirection[1]);
	write_delta_float(buf, from->aimdirection[2], to->aimdirection[2]);

	write_delta_float(buf, from->forwardmove, to->forwardmove);
	write_delta_float(buf, from->sidemove, to->sidemove);
	write_delta_float(buf, from->upmove, to->upmove);

	write_delta_int(buf, from->buttons, to->buttons, 32);
	write_delta_int(buf, from->impulse, to->impulse, 8);

	if (write_delta_int(buf, from->weaponselect, to->weaponselect, 11))
		write_delta_int(buf, from->weaponsubtype, to->weaponsubtype, 6);

	write_delta_short(buf, from->mousedx, to->mousedx);
	write_delta_short(buf, from->mousedy, to->mousedy);
}

void c_messages::fix_move_cmd(CCLCMsg_Move* message) {
    if (versions->server > 13764 || versions->local <= 13764)
        return;

    int cmds = message->num_new_commands() + message->num_backup_commands();
	std::string str = message->data();

	char buf[4000]{};
	c_user_cmd commands[64];
	c_bit_read read(const_cast<char*>(str.c_str()), str.size());
	c_bf_write write(buf, sizeof(buf));

	auto empty_cmd = c_user_cmd();
	auto from = &empty_cmd;
	
	for (auto cmd = 0; cmd < cmds; cmd++) {
		auto move = &commands[cmd];
		read_user_cmd(&read, move, from);
		write_user_cmd(&write, move, from);
		from = move;
	}

	message->set_data(buf, write.current_byte());
}