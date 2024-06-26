enum congrats
{
	CONGRATS_P1_WIN,
	CONGRATS_P2_WIN,
	CONGRATS_DRAW
};

typedef struct dseg3
{
	uint32_t size;                     // 0x000
	char     tables[8];                // 0x004
	char     debug[196];               // 0x00c
	char     congrats_score[72];       // 0x0d0
	char     jty[4];                   // 0x118
	char     asc[12];                  // 0x11c
	char     congrats_condition[3][48];// 0x128
	char     file_error[12];           // 0x1b8

	struct file_path
	{
		char     lev05d_dat[20];      // 0x1c4
		char     hiscore_dat[20];     // 0x1d8
		char     tunnel_dat[44];      // 0x1ec
		char     tables_dat[16];      // 0x208
		char     3dobs_dat[16];       // 0x218
		char     3dpoints_dat[20];    // 0x228
		char     3dfaces_dat[20];     // 0x23c
		char     tex02d_dat[2][44];   // 0x250
	};
	char     unknown[124];             // 0x2A8
	char     bf_music[64];             // 0x324
	char     none[8];                  // 0x364
	char     bf_sound[20];             // 0x36c
	char	 none_0[8];                // 0x3a4
} dseg3_t;

typedef struct dseg3_940
{
	int16_t myvx;                      // 0x940
	int16_t xlimit;                    // 0x942
	int16_t vx;                        // 0x944
	int16_t ylimit;                    // 0x946
	int16_t vy;                        // 0x948
	int16_t foo;                       // 0x94a
	int8_t  no_players;                // 0x94c
	int8_t  temp_no_player[2];         // 0x94d
	int8_t  game_mode;                 // 0x95f
	int8_t  level_no;                  // 0x950
	int8_t  hiscore_ticks;             // 0x951
	int8_t  fading;                    // 0x952
	int8_t  ascii;                     // 0x953
	int8_t  bodge;                     // 0x954
	int8_t  cheat_on;                  // 0x955
	int8_t  game_pause;                // 0x956
	int16_t level_start;               // 0x957
	int8_t  quit_game[3];              // 0x959
	int8_t  race_finished;             // 0x95C
	int8_t  bonus_game;                // 0x95D
	int8_t  new_ship_pitch;            // 0x95E
	int8_t  current_ship_pitch;        // 0x960
	int8_t  hiscore_lookup;            // 0x976
	int8_t  hiscore_second;            // 0x982
	int16_t byte_21fA2A;               // 0xa2a
	int8_t  swamp_blocks[62];          // 0xa2c
	int16_t byte_21FA68;               // 0xa68
	int16_t ice_blocks[44];            // 0xa6a
	int16_t byte_21FAC0;               // 0xac0
	int16_t death_blocks[17];          // 0xac2
	int16_t byte_21FAE0;               // 0xae4
	int16_t jump_blocks[16];           // 0xae6
	int16_t byte_21fb06;               // 0xb06
	int16_t arrow_up_blocks[2];        // 0xb08
	int16_t byte_21FB1A;               // 0xb1a
	int16_t arrow_down_blocks;         // 0xb1c
	int16_t byte_21FB2E;               // 0xb2e
	int16_t BYTE_21fb76;               // 0xb76
	int16_t byte_21FBDE;               // 0xbde
	int16_t arrow_left_blocks[11];     // 0xb30
	int16_t arrow_right_block[52];     // 0xb78
	int16_t reverse_all_blocks[45];    // 0xbe0
	int16_t byte_21FC38;               // 0xc38
	int16_t reverse_x_blocks[74];      // 0xc3a
	int16_t unk_21FC42;                // 0xc42
	int16_t reverse_y_blocks;          // 0xc44
	int16_t byte_21FCCC;               // 0xccc
	int16_t solid_blocks[135];         // 0xcce
	int16_t byte_21FDDsA;              // 0xdda
	int16_t hit_blocks;                // 0xddc
	int16_t word_12fdde[72];           // 0xdde
        int16_t byte_21FE6C;               // 0xe6c
	int16_t contact_blocks;            // 0xe6e
	int16_t anim_order_1[41];          // 0xe70
	int16_t anim_order_2[41];          // 0xec2
        int16_t anim_order_3[41];          // 0xf14
        int16_t anim_order_4[41];          // 0xf66
	int16_t anim_order_5[67];          // 0xfb8
	int16_t anim_order_6[67];          // 0x103e
        int16_t anim_order_7[67];          // 0x10c4
        int16_t anim_order_8[67];          // 0x114a
	int16_t anim_order_9[67];          // 0x11d0
	int16_t anim_order_10[67];         // 0x1256
	int16_t anim_order_11[67];         // 0x12dc
	int16_t anim_order_12[67];         // 0x1362
	int16_t anim_order_13[67];         // 0x13e8
        int16_t anim_order_14[67];         // 0x146e
	int16_t anim_order_15[67];         // 0x14f4
	int16_t anim_order_16[67];         // 0x157a
	int16_t anim_order_17[67];         // 0x1600
	int16_t anim_order_18[67];         // 0x1686
	int16_t anim_order_19[67];         // 0x170c
	int16_t anim_order_20[67];         // 0x1792
	int16_t anim_order_21[21];         // 0x1818
	int16_t anim_order_22[21];         // 0x1842
	int16_t anim_order_23[21];         // 0x186c
	int16_t anim_order_24[21];         // 0x1896
	int16_t anim_order_25[21];         // 0x18c0
	int16_t anim_order_26[21];         // 0x18ea
	int16_t anim_order_27[11];         // 0x1914
	int16_t anim_order_28[7];          // 0x1922
	int16_t anim_order_29[7];          // 0x1930
	int16_t anim_order_30[7];          // 0x193e
	int16_t anim_order_31[7];          // 0x194c
	int16_t anim_order_32[7];          // 0x195a
	int16_t anim_order_33[7];          // 0x1968
	int16_t anim_order_34[7];          // 0x1976
	int16_t anim_order_35[7];          // 0x1984
	int16_t anim_order_36[7];          // 0x1992
	int16_t anim_order_37[7];          // 0x19a0
        int16_t anim_order_38[7];          // 0x19ae
	int16_t array_list[7];             // 0x19bc
	char* byte_220A58;                 // 0x1a58
	char* byte_220A59;                 // 0x1a59
        char startup_files[544];           // 0x1a64
	char  byte_220C44[4];              // 0x1c44
	int16_t word_220C48;               // 0x1c48
	int16_t word_220C4A;               // 0x1c4a
	int32_t dword_220C4C;              // 0x1c4c
	int32_t vec_screen;                // 0x1c50
	int32_t vec_map;                   // 0x1c54
	int32_t vec_screen_width;          // 0x1c58
	int32_t vec_window_width;          // 0x1c5c
	int32_t vec_window_height;         // 0x1c60
	int32_t polyscans;                 // 0x1c64
	char vec_colour;                   // 0x4964
        char vec_mode;                     // 0x4965
	int sintable[512];                 // 0x4968
	int costable[512];                 // 0x5168
	int32_t dword_226168;              // 0x7168
	int32_t dword_22616C;              // 0x716c
	char KeyboardInstalled;            // 0x7180
	char inkey_asckey;                 // 0x7181
	int32_t GlassMap;                  // 0x71f4
	char fade_started[4];              // 0x71f8
        int16_t DrawFlags;                 // 0x71fc
	int32_t Network;                   // 0x7284
	int32_t dword_22628C;              // 0x728c
	int32_t dword_226290;              // 0x7290
	int32_t dword_226294;              // 0x7294
	int32_t dword_226298;              // 0x7298
	char music_tablea[256];            // 0x72d4
	char SoundInfoDirectory[52];       // 0x73d4
	char SoundInfoFilcce[680];         // 0x7408
	char SoundAble;                    // 0x76b0
	char SoundActive;                  // 0x76b1
	char MusicAble;                    // 0x7999
	char MusicActive;                  // 0x799a
	int dword_22D444;                  // 0xe444
	int dword_22D448;                  // 0xe448
	int16_t word_22D44E;               // 0xe44e
	int16_t word_22D450;               // 0xe450
	int16_t word_22D452;               // 0xe452
	char byte_22D454;                  // 0xe454
	char byte_22D455;                  // 0xe455
	int32_t dword_22ED90;              // 0xfd90
	char colour_lookup;                // 0xfda0
	char byte_22EDA1;                  // 0xfda1
	char byte_22EDA2;                  // 0xfda2
	char byte_22EDA3;                  // 0xfda3
	char byte_22EDA4;                  // 0xfda4
	char byte_22EDA5;                  // 0xfda5
	char byte_22EDA6;                  // 0xfda6
	char byte_22EDA7;                  // 0xfda7
	int16_t anim_blks;                 // 0xfda8
        int16_t dword_22EDAA;              // 0xfdaa
	int16_t word_22EDAE;               // 0xfdae
        int16_t word_22EDB0;               // 0xfdb0
} dseg3_940_t;
