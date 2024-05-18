#include "Func.h"

Color ColorFromHex(int hexValue) {
	unsigned char r = (hexValue >> 16) & 0xFF;
	unsigned char g = (hexValue >> 8) & 0xFF;
	unsigned char b = hexValue & 0xFF;
	return Color{ r, g, b, 255 };
}

Color Theme_of_element(string element) {
	if (element == "ELECTRIC") return ColorFromHex(0xEED626);
	if (element == "FIRE") return ORANGE;
	if (element == "NATURE") return GREEN;
	if (element == "PSYCHIC") return GRAY;
	if (element == "WATER") return BLUE;
	if (element == "POISON") return PURPLE;
}

Color Theme_of_Weakness(string weakness) {
	if (weakness == "ELECTRIC") return ColorFromHex(0xEED626);
	if (weakness == "FIRE") return ORANGE;
	if (weakness == "NATURE") return GREEN;
	if (weakness == "PSYCHIC") return GRAY;
	if (weakness == "WATER") return BLUE;
	if (weakness == "POISON") return PURPLE;
}

void DrawInfo(vector<Pokemon>& pokemons) {
	for (int i = 0; i < 6; i++) {
		DrawTexture(pokemons[i].texture, i * 360, 320, WHITE);
		string info_name = "Name: " + pokemons[i].name;
		string info_health = "Health: " + to_string(pokemons[i].health);
		string info_damage = "Damage: " + to_string(pokemons[i].damage);
		string info_mana1 = "Mana: ";
		string info_mana2 = to_string(pokemons[i].mana);
		string info_element1 = "Element: ";
		string info_element2 = pokemons[i].element;
		string info_weakness1 = "Weakness: ";
		string info_weakness2 = pokemons[i].weakness;
		DrawTextEx(font, info_name.c_str(), Vector2{ float(i * 360 + 30), 620 }, 40, 0, BLACK);
		DrawTextEx(font, info_health.c_str(), Vector2{ float(i * 360 + 30), 670 }, 40, 0, BLACK);
		DrawTextEx(font, info_damage.c_str(), Vector2{ float(i * 360 + 30), 720 }, 40, 0, BLACK);
		DrawTextEx(font, info_mana1.c_str(), Vector2{ float(i * 360 + 30), 770 }, 40, 0, BLACK);
		DrawTextEx(font, info_mana2.c_str(), Vector2{ float(i * 360 + 130), 770 }, 40, 0, BLUE);
		DrawTextEx(font, info_element1.c_str(), Vector2{ float(i * 360 + 30), 820 }, 40, 0, BLACK);
		DrawTextEx(font, info_element2.c_str(), Vector2{ float(i * 360 + 165), 820 }, 40, 0, Theme_of_element(pokemons[i].element));
		DrawTextEx(font, info_weakness1.c_str(), Vector2{ float(i * 360 + 30), 870 }, 40, 0, BLACK);
		DrawTextEx(font, info_weakness2.c_str(), Vector2{ float(i * 360 + 200), 870 }, 40, 0, Theme_of_Weakness(pokemons[i].weakness));
	}
}


vector<Pokemon> choose_the_pokemon(vector<Pokemon>& mass, vector<Pokemon>& mass_end, int& mod, int& pos_x) {
	if (mod > 0) {
		DrawTexture(arrow, pos_x, 940, WHITE);
		if (pos_x != 120 && pos_x != 1920) {
			if (IsKeyPressed(KEY_RIGHT)) {
				pos_x += 360;
			}
			if (IsKeyPressed(KEY_LEFT)) {
				pos_x -= 360;
			}
		}
		if (pos_x == 120) {
			if (IsKeyPressed(KEY_RIGHT)) {
				pos_x += 360;

			}
		}
		if (pos_x == 1920) {
			if (IsKeyPressed(KEY_LEFT)) {
				pos_x -= 360;
			}
		}

		if (IsKeyPressed(KEY_ENTER)) {
			switch (pos_x)
			{
				case 120:
					mass_end.push_back(mass[0]);
					break;
				case 480:
					mass_end.push_back(mass[1]);
					break;
				case 840:
					mass_end.push_back(mass[2]);
					break;
				case 1200:
					mass_end.push_back(mass[3]);
					break;
				case 1560:
					mass_end.push_back(mass[4]);
					break;
				case 1920:
					mass_end.push_back(mass[5]);
					break;
				default:
					break;
			}
			mod--;
		}
	}
	return mass_end;
}

void other_pokemons() {

}

void fight(vector <Pokemon>& mass_for_player1, vector <Pokemon>& mass_for_player2, int cnt, int& pos_y, int& pos_x, int& player_for_fight, Texture2D texLightning, Image imLightning) {
	if (cnt == 1) {
		string message = "Player " + to_string(player_for_fight) + " attack the enemy";
		DrawTextEx(font, message.c_str(), Vector2{ 750, 150 }, 64, 0, BLACK);
		DrawTexture(mass_for_player1[0].texture, 200, 520, WHITE);
		DrawTextEx(font, ("Health: " + to_string(mass_for_player1[0].health)).c_str(), Vector2{ 200, 820 }, 64, 0, RED);
		DrawTextEx(font, ("Mana: " + to_string(mass_for_player1[0].mana)).c_str(), Vector2{ 200, 900 }, 64, 0, BLUE);
		DrawTexture(mass_for_player2[0].texture, 1650, 520, WHITE);
		DrawTextEx(font, ("Health: " + to_string(mass_for_player2[0].health)).c_str(), Vector2{ 1650, 820 }, 64, 0, RED);
		DrawTextEx(font, ("Mana: " + to_string(mass_for_player2[0].mana)).c_str(), Vector2{ 1650, 900 }, 64, 0, BLUE);

		vector <Pokemon>& mass_for_me = (player_for_fight == 1) ? mass_for_player1 : mass_for_player2;
		vector <Pokemon>& mass_for_enemy = (player_for_fight == 1) ? mass_for_player2 : mass_for_player1;

		string message1 = "Default attack";
		DrawTextEx(font, message1.c_str(), Vector2{ 900, 520 }, 74, 0, BLACK);
		DrawTexture(arrow_left, 1200, pos_y, WHITE);
		string message2 = "Super attack";
		DrawTextEx(font, message2.c_str(), Vector2{ 900, 620 }, 74, 0, BLACK);
		string message6 = "Skip";
		DrawTextEx(font, message6.c_str(), Vector2{ 900, 720 }, 74, 0, BLACK);
		bool position_changed = false;
		if (mass_for_me[0].mana < 10) pos_y = 630;
		if (!position_changed && pos_y == 430) {
			if (mass_for_me[0].mana - 25 < 0) {
				if (IsKeyPressed(KEY_DOWN)) {
					pos_y += 200;
					position_changed = true;
				}
			}
			else if (!position_changed && IsKeyPressed(KEY_DOWN)) {
				pos_y += 100;
				position_changed = true;
			}
			string message3 = "Damage: " + to_string(mass_for_me[0].damage);
			DrawTextEx(font, message3.c_str(), { 900, 900 }, 80, 0, BLACK);

			if (IsKeyPressed(KEY_SPACE)) {
				mass_for_me[0].mana -= 10;
				if (mass_for_enemy[0].weakness == mass_for_me[0].element) {
					mass_for_enemy[0].health -= int(mass_for_me[0].damage * 1.2);
				}
				else {
					mass_for_enemy[0].health -= mass_for_me[0].damage;
				}
				if (mass_for_enemy[0].health < 0) {
					mass_for_enemy[0].health = 0;
				}
				if (player_for_fight == 1) {
					player_for_fight = 2;
				}
				else {
					player_for_fight = 1;
				}
			}
		}
		if (!position_changed && pos_y == 530) {
			if (IsKeyPressed(KEY_UP)) {
				pos_y -= 100;
				position_changed = true;
			}
			else if (!position_changed && IsKeyPressed(KEY_DOWN)) {
				pos_y += 100;
				position_changed = true;
			}
			string message4 = mass_for_me[0].special_name;
			DrawTextEx(font, message4.c_str(), { 900, 900 }, 80, 0, BLACK);
			float deltaTime = GetFrameTime();
			if (IsKeyPressed(KEY_SPACE)) {
				isShowing = true;
				timer = 0.0f;
				isPlaying = true;
				currentAnimFrame = 0;
				frameCounter = 0;
				currentPos1 = startPos1;
				currentPos2 = startPos2;
				currentPos_for_wave = startPos_for_wave;
				currentPos2_for_wave = startPos2_for_wave;
			}
			NameOfSuper name_of_super;
			if (mass_for_me[0].special_name == "Electric_stan") name_of_super = Electric_stan;
			else if (mass_for_me[0].special_name == "Fireball") name_of_super = Fireball;
			else if (mass_for_me[0].special_name == "Entangling_vine") name_of_super = Entangling_vine;
			else if (mass_for_me[0].special_name == "Tsunami") name_of_super = Tsunami;
			else if (mass_for_me[0].special_name == "Mind_Attack") name_of_super = Mind_Attack;
			else if (mass_for_me[0].special_name == "Poisonous_cloud") name_of_super = Poisonous_cloud;

			switch (name_of_super)
			{
				case Electric_stan: {
					if (isPlaying) {
						frameCounter++;
						if (frameCounter >= frameDelay) {
							currentAnimFrame++;
							if (currentAnimFrame >= animFrames_for_light) {
								currentAnimFrame = 0;
								isPlaying = false;
								if (mass_for_enemy[0].weakness == mass_for_me[0].element) {
									mass_for_enemy[0].health -= int(mass_for_me[0].special_damage * 1.2);
								}
								else {
									mass_for_enemy[0].health -= mass_for_me[0].special_damage;
								}
								mass_for_me[0].mana -= 25;
								if (mass_for_enemy[0].health - mass_for_me[0].special_damage < 0) {
									mass_for_enemy[0].health = 0;
								}
								if (player_for_fight == 1) player_for_fight = 2;
								else player_for_fight = 1;
								pos_y = 430;
							}
							nextFrameDataOffset = imLightning.width * imLightning.height * 4 * currentAnimFrame;
							UpdateTexture(texLightning, ((unsigned char*)imLightning.data) + nextFrameDataOffset);
							frameCounter = 0;
						}
						if (player_for_fight == 1) {
							DrawTexture(texLightning, 1560, 380, WHITE);
						}
						else {
							DrawTexture(texLightning, 130, 380, WHITE);
						}
					}
					break;
				}
				case Fireball: {
					if (isPlaying) {
						frameCounter++;
						if (frameCounter >= frameDelay) {
							currentAnimFrame++;
							if (currentAnimFrame >= animFrames_for_fire) {
								currentAnimFrame = 0;
							}
							nextFrameDataOffset = imFireball.width * imFireball.height * 4 * currentAnimFrame;
							UpdateTexture(texFireball, ((unsigned char*)imFireball.data) + nextFrameDataOffset);
							UpdateTexture(texFireball2, ((unsigned char*)imFireball2.data) + nextFrameDataOffset);
							frameCounter = 0;
						}

						if (player_for_fight == 1) {
							if (currentPos1.x < endPos1.x)
							{
								currentPos1.x += 10;
								if (currentPos1.x >= endPos1.x)
								{
									currentPos1 = endPos1;
									if (mass_for_enemy[0].weakness == mass_for_me[0].element) {
										mass_for_enemy[0].health -= int(mass_for_me[0].special_damage * 1.2);
									}
									else {
										mass_for_enemy[0].health -= mass_for_me[0].special_damage;
									}
									mass_for_me[0].mana -= 25;
									if (mass_for_enemy[0].health - mass_for_me[0].special_damage < 0) {
										mass_for_enemy[0].health = 0;
									}
									isPlaying = false;
									if (player_for_fight == 1) {
										player_for_fight = 2;
										pos_y = 430;
									}
									else {
										player_for_fight = 1;
										pos_y = 430;
									}
								}
							}
							DrawTexture(texFireball, (int)currentPos1.x, (int)currentPos1.y, WHITE);
						}
						else {
							if (currentPos2.x > endPos2.x)
							{
								currentPos2.x -= 10;
								if (currentPos2.x <= endPos2.x)
								{
									currentPos2 = endPos2;
									if (mass_for_enemy[0].weakness == mass_for_me[0].element) {
										mass_for_enemy[0].health -= int(mass_for_me[0].special_damage * 1.2);
									}
									else {
										mass_for_enemy[0].health -= mass_for_me[0].special_damage;
									}
									mass_for_me[0].mana -= 25;
									if (mass_for_enemy[0].health - mass_for_me[0].special_damage < 0) {
										mass_for_enemy[0].health = 0;
									}
									isPlaying = false;
									if (player_for_fight == 1) {
										player_for_fight = 2;
										pos_y = 430;
									}
									else {
										player_for_fight = 1;
										pos_y = 430;
									}
								}
							}
							DrawTexture(texFireball2, (int)currentPos2.x, (int)currentPos2.y, WHITE);
						}
					}
					break;
				}
				case Tsunami: {
					if (isPlaying) {
						frameCounter++;
						if (frameCounter >= frameDelay) {
							frameCounter = 0;
							currentAnimFrame++;
							if (currentAnimFrame >= 11) {
								currentAnimFrame = 0;
							}
						}
						float frameWidth = (float)(texWave.width / 11);
						Rectangle frameRec = { frameWidth * currentAnimFrame, 0, frameWidth, (float)texWave.height };
						float frameWidth2 = (float)(texWave2.width / 11);
						Rectangle frameRec2 = { frameWidth2 * currentAnimFrame, 0, frameWidth2, (float)texWave2.height };

						if (player_for_fight == 1) {
							if (currentPos_for_wave.x < endPos_for_wave.x) {
								currentPos_for_wave.x += 20;
								if (currentPos_for_wave.x >= endPos_for_wave.x) {
									currentPos_for_wave = endPos_for_wave;
									isPlaying = false;
									if (mass_for_enemy[0].weakness == mass_for_me[0].element) {
										mass_for_enemy[0].health -= int(mass_for_me[0].special_damage * 1.2);
									}
									else {
										mass_for_enemy[0].health -= mass_for_me[0].special_damage;
									}
									mass_for_me[0].mana -= 25;
									if (mass_for_enemy[0].health - mass_for_me[0].special_damage < 0) {
										mass_for_enemy[0].health = 0;
									}
									player_for_fight = 2;
									pos_y = 430;
								}
							}
							DrawTextureRec(texWave, frameRec, currentPos_for_wave, WHITE);
						}
						else {
							if (currentPos2_for_wave.x > endPos2_for_wave.x) {
								currentPos2_for_wave.x -= 20;
								if (currentPos2_for_wave.x <= endPos2_for_wave.x) {
									currentPos2_for_wave = endPos2_for_wave;
									isPlaying = false;
									if (mass_for_enemy[0].weakness == mass_for_me[0].element) {
										mass_for_enemy[0].health -= int(mass_for_me[0].special_damage * 1.2);
									}
									else {
										mass_for_enemy[0].health -= mass_for_me[0].special_damage;
									}
									mass_for_me[0].mana -= 25;
									if (mass_for_enemy[0].health - mass_for_me[0].special_damage < 0) {
										mass_for_enemy[0].health = 0;
									}
									player_for_fight = 1;
									pos_y = 430;
								}
							}
							DrawTextureRec(texWave2, frameRec2, currentPos2_for_wave, WHITE);
						}
					}
					break;
				}
							/*case Entangling_vine: {
								if (isShowing) {
									if (player_for_fight == 1) {
										DrawTexture(texGrass, 1690, 700, WHITE);
									}
									else {
										DrawTexture(texGrass, 200, 570, WHITE);
									}
								}
								break;
							}
							case Poisonous_cloud: {
								if (isPlaying) {
									frameCounter++;
									if (frameCounter >= frameDelay) {
										frameCounter = 0;
										currentAnimFrame++;
										if (currentAnimFrame >= 40) {
											isPlaying = false;
											player_for_fight = (player_for_fight == 1) ? 2 : 1;
										}
										UpdateTexture(texPoison, ((unsigned char*)imPoison.data) + nextFrameDataOffset);
									}
									float frameWidth = (float)(texPoison.width / 40);
									Rectangle frameRec = { frameWidth * currentAnimFrame, 0, frameWidth, (float)texPoison.height };

									if (player_for_fight == 1) {
										DrawTextureRec(texPoison, frameRec, currentPos_for_cloud, WHITE);
									}
									else {
										DrawTextureRec(texPoison, frameRec, currentPos2_for_cloud, WHITE);
									}
								}
								break;
							}*/
			}
		}
		if (!position_changed && pos_y == 630) {
			string message5 = "Mana +10";
			DrawTextEx(font, message5.c_str(), { 900, 900 }, 80, 0, BLACK);
			if (mass_for_me[0].mana - 10 < 0) {
				if (IsKeyPressed(KEY_SPACE)) {
					if (mass_for_me[0].mana + 10 <= 100) {
						mass_for_me[0].mana += 10;
						if (player_for_fight == 1) player_for_fight = 2;
						else player_for_fight = 1;
						pos_y = 430;
					}
				}
			}
			else if (mass_for_me[0].mana - 25 < 0) {
				if (IsKeyPressed(KEY_UP)) {
					pos_y -= 200;
					position_changed = true;
				}
				if (IsKeyPressed(KEY_SPACE)) {
					if (mass_for_me[0].mana + 10 <= 100) {
						mass_for_me[0].mana += 10;
						if (player_for_fight == 1) player_for_fight = 2;
						else player_for_fight = 1;
						pos_y = 430;
					}
				}
			}
			else {
				if (!position_changed && IsKeyPressed(KEY_UP)) {
					pos_y -= 100;
					position_changed = true;
				}
				if (IsKeyPressed(KEY_SPACE)) {
					if (mass_for_me[0].mana + 10 <= 100) {
						mass_for_me[0].mana += 10;
						if (player_for_fight == 1) player_for_fight = 2;
						else player_for_fight = 1;
						pos_y = 430;
					}
				}
			}
		}
		if (mass_for_player1[0].health == 0) {
			DrawTextEx(font, "Player 2 win", Vector2{ 700, 1100 }, 150, 0, BLACK);
		}
		else if (mass_for_player2[0].health == 0) {
			DrawTextEx(font, "Player 1 win", Vector2{ 700, 1100 }, 150, 0, BLACK);
		}
	}
	if (cnt == 3) {
		bool position_changed = false;
		if (!choosed_pokemon1) {
			string message = "Player 1 choose you pokemon";
			DrawTextEx(font, message.c_str(), Vector2{ 750, 150 }, 64, 0, BLACK);
			DrawTexture(mass_for_player1[0].texture, 200, 320, WHITE);
			DrawTextEx(font, ("Health: " + to_string(mass_for_player1[0].health)).c_str(), Vector2{ 200, 620 }, 64, 0, RED);
			DrawTextEx(font, ("Mana: " + to_string(mass_for_player1[0].mana)).c_str(), Vector2{ 200, 700 }, 64, 0, BLUE);
			DrawTexture(mass_for_player1[1].texture, 900, 320, WHITE);
			DrawTextEx(font, ("Health: " + to_string(mass_for_player1[1].health)).c_str(), Vector2{ 900, 620 }, 64, 0, RED);
			DrawTextEx(font, ("Mana: " + to_string(mass_for_player1[1].mana)).c_str(), Vector2{ 900, 700 }, 64, 0, BLUE);
			DrawTexture(mass_for_player1[2].texture, 1700, 320, WHITE);
			DrawTextEx(font, ("Health: " + to_string(mass_for_player1[2].health)).c_str(), Vector2{ 1700, 620 }, 64, 0, RED);
			DrawTextEx(font, ("Mana: " + to_string(mass_for_player1[2].mana)).c_str(), Vector2{ 1700, 700 }, 64, 0, BLUE);
			DrawTexture(arrow, pos_x, 850, WHITE);
			if (!position_changed && pos_x == 250) {
				if (IsKeyPressed(KEY_RIGHT)) {
					pos_x += 750;
					position_changed = true;
				}
				if (IsKeyPressed(KEY_ENTER)) {
					i1 = 0;
					choosed_pokemon1 = true;
				}
			}
			if (!position_changed && pos_x == 1000) {
				if (IsKeyPressed(KEY_RIGHT)) {
					pos_x += 750;
					position_changed = true;
				}
				if (IsKeyPressed(KEY_LEFT)) {
					pos_x -= 750;
					position_changed = true;
				}
				if (IsKeyPressed(KEY_ENTER)) {
					i1 = 1;
					choosed_pokemon1 = true;
				}
			}
			if (!position_changed && pos_x == 1750) {
				if (IsKeyPressed(KEY_LEFT)) {
					pos_x -= 750;
					position_changed = true;
				}
				if (IsKeyPressed(KEY_ENTER)) {
					i1 = 2;
					choosed_pokemon1 = true;
				}
			}
			if (choosed_pokemon1) pos_x = 250;
		}
		else if (!choosed_pokemon2) {
			string message = "Player 2 choose you pokemon";
			DrawTextEx(font, message.c_str(), Vector2{ 750, 150 }, 64, 0, BLACK);
			DrawTexture(mass_for_player2[0].texture, 200, 320, WHITE);
			DrawTextEx(font, ("Health: " + to_string(mass_for_player2[0].health)).c_str(), Vector2{ 200, 620 }, 64, 0, RED);
			DrawTextEx(font, ("Mana: " + to_string(mass_for_player2[0].mana)).c_str(), Vector2{ 200, 700 }, 64, 0, BLUE);
			DrawTexture(mass_for_player2[1].texture, 900, 320, WHITE);
			DrawTextEx(font, ("Health: " + to_string(mass_for_player2[1].health)).c_str(), Vector2{ 900, 620 }, 64, 0, RED);
			DrawTextEx(font, ("Mana: " + to_string(mass_for_player2[01].mana)).c_str(), Vector2{ 900, 700 }, 64, 0, BLUE);
			DrawTexture(mass_for_player2[2].texture, 1700, 320, WHITE);
			DrawTextEx(font, ("Health: " + to_string(mass_for_player2[2].health)).c_str(), Vector2{ 1700, 620 }, 64, 0, RED);
			DrawTextEx(font, ("Mana: " + to_string(mass_for_player2[2].mana)).c_str(), Vector2{ 1700, 700 }, 64, 0, BLUE);
			DrawTexture(arrow, pos_x, 850, WHITE);
			if (!position_changed && pos_x == 250) {
				if (IsKeyPressed(KEY_RIGHT)) {
					pos_x += 750;
					position_changed = true;
				}
				if (IsKeyPressed(KEY_ENTER)) {
					i2 = 0;
					choosed_pokemon2 = true;
				}
			}
			if (!position_changed && pos_x == 1000) {
				if (IsKeyPressed(KEY_RIGHT)) {
					pos_x += 750;
					position_changed = true;
				}
				if (IsKeyPressed(KEY_LEFT)) {
					pos_x -= 750;
					position_changed = true;
				}
				if (IsKeyPressed(KEY_ENTER)) {
					i2 = 1;
					choosed_pokemon2 = true;
				}
			}
			if (!position_changed && pos_x == 1750) {
				if (IsKeyPressed(KEY_LEFT)) {
					pos_x -= 750;
					position_changed = true;
				}
				if (IsKeyPressed(KEY_ENTER)) {
					i2 = 2;
					choosed_pokemon2 = true;
				}
			}
		}
		if (choosed_pokemon1 && choosed_pokemon2) {
			string message = "Player " + to_string(player_for_fight) + " attack the enemy";
			DrawTextEx(font, message.c_str(), Vector2{ 750, 150 }, 64, 0, BLACK);
			DrawTexture(mass_for_player1[i1].texture, 200, 520, WHITE);
			DrawTextEx(font, ("Health: " + to_string(mass_for_player1[i1].health)).c_str(), Vector2{ 200, 820 }, 64, 0, RED);
			DrawTextEx(font, ("Mana: " + to_string(mass_for_player1[i1].mana)).c_str(), Vector2{ 200, 900 }, 64, 0, BLUE);
			DrawTexture(mass_for_player2[i2].texture, 1650, 520, WHITE);
			DrawTextEx(font, ("Health: " + to_string(mass_for_player2[i2].health)).c_str(), Vector2{ 1650, 820 }, 64, 0, RED);
			DrawTextEx(font, ("Mana: " + to_string(mass_for_player2[i2].mana)).c_str(), Vector2{ 1650, 900 }, 64, 0, BLUE);

			vector <Pokemon>& mass_for_me = (player_for_fight == 1) ? mass_for_player1 : mass_for_player2;
			vector <Pokemon>& mass_for_enemy = (player_for_fight == 1) ? mass_for_player2 : mass_for_player1;

			string message1 = "Default attack";
			DrawTextEx(font, message1.c_str(), Vector2{ 850, 520 }, 74, 0, BLACK);
			string message2 = "Super attack";
			DrawTextEx(font, message2.c_str(), Vector2{ 850, 620 }, 74, 0, BLACK);
			string message6 = "Skip";
			DrawTextEx(font, message6.c_str(), Vector2{ 850, 720 }, 74, 0, BLACK);
			string message7 = "Others pokemon";
			DrawTextEx(font, message7.c_str(), Vector2{ 850, 820 }, 74, 0, BLACK);
			DrawTexture(arrow_left, 1250, pos_y, WHITE);
			int i = (player_for_fight == 1) ? i1 : i2;
			if (mass_for_me[i].health == 0 && mass_for_me.size() != 1) {
				mass_for_me.erase(mass_for_me.begin() + i);
			}
			if (mass_for_me[i].mana < 10) pos_y = 630;
			if (!position_changed && pos_y == 430) {
				if (mass_for_me[i].mana - 25 < 0) {
					if (IsKeyPressed(KEY_DOWN)) {
						pos_y += 200;
						position_changed = true;
					}
				}
				else if (!position_changed && IsKeyPressed(KEY_DOWN)) {
					pos_y += 100;
					position_changed = true;
				}
				string message3 = "Damage: " + to_string(mass_for_me[i1].damage);
				DrawTextEx(font, message3.c_str(), { 850, 950 }, 80, 0, BLACK);

				if (IsKeyPressed(KEY_SPACE)) {
					mass_for_me[i].mana -= 10;
					if (player_for_fight == 1) {
						if (mass_for_enemy[i2].weakness == mass_for_me[i1].element) {
							mass_for_enemy[i2].health -= int(mass_for_me[i1].damage * 1.2);
						}
						else {
							mass_for_enemy[i2].health -= mass_for_me[i1].damage;
						}
						if (mass_for_enemy[i2].health < 0) {
							mass_for_enemy[i2].health = 0;
						}
						player_for_fight = 2;
					}
					else {
						if (mass_for_enemy[i1].weakness == mass_for_me[i2].element) {
							mass_for_enemy[i1].health -= int(mass_for_me[i2].damage * 1.2);
						}
						else {
							mass_for_enemy[i1].health -= mass_for_me[i2].damage;
						}
						if (mass_for_enemy[i1].health < 0) {
							mass_for_enemy[i1].health = 0;
						}
						player_for_fight = 1;
					}
				}
			}

			if (!position_changed && pos_y == 530) {
				if (IsKeyPressed(KEY_DOWN)) {
					pos_y += 100;
					position_changed = true;
				}
				else if (IsKeyPressed(KEY_UP)) {
					pos_y -= 100;
					position_changed = true;
				}

				string message4 = mass_for_me[i].special_name;
				DrawTextEx(font, message4.c_str(), { 850, 950 }, 80, 0, BLACK);
				float deltaTime = GetFrameTime();
				if (IsKeyPressed(KEY_SPACE)) {
					isShowing = true;
					timer = 0.0f;
					isPlaying = true;
					currentAnimFrame = 0;
					frameCounter = 0;
					currentPos1 = startPos1;
					currentPos2 = startPos2;
					currentPos_for_wave = startPos_for_wave;
					currentPos2_for_wave = startPos2_for_wave;
				}
				NameOfSuper name_of_super;
				if (mass_for_me[i].special_name == "Electric_stan") name_of_super = Electric_stan;
				else if (mass_for_me[i].special_name == "Fireball") name_of_super = Fireball;
				else if (mass_for_me[i].special_name == "Entangling_vine") name_of_super = Entangling_vine;
				else if (mass_for_me[i].special_name == "Tsunami") name_of_super = Tsunami;
				else if (mass_for_me[i].special_name == "Mind_Attack") name_of_super = Mind_Attack;
				else if (mass_for_me[i].special_name == "Poisonous_cloud") name_of_super = Poisonous_cloud;

				switch (name_of_super)
				{
					case Electric_stan: {
						if (isPlaying) {
							frameCounter++;
							if (frameCounter >= frameDelay) {
								currentAnimFrame++;
								if (currentAnimFrame >= animFrames_for_light) {
									currentAnimFrame = 0;
									isPlaying = false;
									if (player_for_fight == 1) {
										if (mass_for_enemy[i2].weakness == mass_for_me[i1].element) {
											mass_for_enemy[i2].health -= int(mass_for_me[i1].special_damage * 1.2);
										}
										else {
											mass_for_enemy[i2].health -= mass_for_me[i1].special_damage;
										}
										mass_for_me[i1].mana -= 25;
										if (mass_for_enemy[i2].health - mass_for_me[i1].special_damage < 0) {
											mass_for_enemy[i2].health = 0;
										}
									}
									else {
										if (mass_for_enemy[i1].weakness == mass_for_me[i2].element) {
											mass_for_enemy[i1].health -= int(mass_for_me[i2].special_damage * 1.2);
										}
										else {
											mass_for_enemy[i2].health -= mass_for_me[i2].special_damage;
										}
										mass_for_me[i2].mana -= 25;
										if (mass_for_enemy[i1].health - mass_for_me[i2].special_damage < 0) {
											mass_for_enemy[i1].health = 0;
										}
									}
									if (player_for_fight == 1) player_for_fight = 2;
									else player_for_fight = 1;
									pos_y = 430;
								}
								nextFrameDataOffset = imLightning.width * imLightning.height * 4 * currentAnimFrame;
								UpdateTexture(texLightning, ((unsigned char*)imLightning.data) + nextFrameDataOffset);
								frameCounter = 0;
							}
							if (player_for_fight == 1) {
								DrawTexture(texLightning, 1560, 380, WHITE);
							}
							else {
								DrawTexture(texLightning, 130, 380, WHITE);
							}
						}
						break;
					}
					case Fireball: {
						if (isPlaying) {
							frameCounter++;
							if (frameCounter >= frameDelay) {
								currentAnimFrame++;
								if (currentAnimFrame >= animFrames_for_fire) {
									currentAnimFrame = 0;
								}
								nextFrameDataOffset = imFireball.width * imFireball.height * 4 * currentAnimFrame;
								UpdateTexture(texFireball, ((unsigned char*)imFireball.data) + nextFrameDataOffset);
								UpdateTexture(texFireball2, ((unsigned char*)imFireball2.data) + nextFrameDataOffset);
								frameCounter = 0;
							}

							if (player_for_fight == 1) {
								if (currentPos1.x < endPos1.x)
								{
									currentPos1.x += 10;
									if (currentPos1.x >= endPos1.x)
									{
										currentPos1 = endPos1;
										if (mass_for_enemy[i2].weakness == mass_for_me[i1].element) {
											mass_for_enemy[i2].health -= int(mass_for_me[i1].special_damage * 1.2);
										}
										else {
											mass_for_enemy[i2].health -= mass_for_me[i1].special_damage;
										}
										mass_for_me[i1].mana -= 25;
										if (mass_for_enemy[i2].health - mass_for_me[i1].special_damage < 0) {
											mass_for_enemy[i2].health = 0;
										}
										isPlaying = false;
										if (player_for_fight == 1) {
											player_for_fight = 2;
											pos_y = 430;
										}
										else {
											player_for_fight = 1;
											pos_y = 430;
										}
									}
								}
								DrawTexture(texFireball, (int)currentPos1.x, (int)currentPos1.y, WHITE);
							}
							else {
								if (currentPos2.x > endPos2.x)
								{
									currentPos2.x -= 10;
									if (currentPos2.x <= endPos2.x)
									{
										currentPos2 = endPos2;
										if (mass_for_enemy[i1].weakness == mass_for_me[i2].element) {
											mass_for_enemy[i1].health -= int(mass_for_me[i2].special_damage * 1.2);
										}
										else {
											mass_for_enemy[i1].health -= mass_for_me[i2].special_damage;
										}
										mass_for_me[i2].mana -= 25;
										if (mass_for_enemy[i1].health - mass_for_me[i2].special_damage < 0) {
											mass_for_enemy[i1].health = 0;
										}
										isPlaying = false;
										if (player_for_fight == 1) {
											player_for_fight = 2;
											pos_y = 430;
										}
										else {
											player_for_fight = 1;
											pos_y = 430;
										}
									}
								}
								DrawTexture(texFireball2, (int)currentPos2.x, (int)currentPos2.y, WHITE);
							}
						}
						break;
					}
					case Tsunami: {
						if (isPlaying) {
							frameCounter++;
							if (frameCounter >= frameDelay) {
								frameCounter = 0;
								currentAnimFrame++;
								if (currentAnimFrame >= 11) {
									currentAnimFrame = 0;
								}
							}
							float frameWidth = (float)(texWave.width / 11);
							Rectangle frameRec = { frameWidth * currentAnimFrame, 0, frameWidth, (float)texWave.height };
							float frameWidth2 = (float)(texWave2.width / 11);
							Rectangle frameRec2 = { frameWidth2 * currentAnimFrame, 0, frameWidth2, (float)texWave2.height };

							if (player_for_fight == 1) {
								if (currentPos_for_wave.x < endPos_for_wave.x) {
									currentPos_for_wave.x += 20;
									if (currentPos_for_wave.x >= endPos_for_wave.x) {
										currentPos_for_wave = endPos_for_wave;
										isPlaying = false;
										if (mass_for_enemy[i2].weakness == mass_for_me[i1].element) {
											mass_for_enemy[i2].health -= int(mass_for_me[i1].special_damage * 1.2);
										}
										else {
											mass_for_enemy[i2].health -= mass_for_me[i1].special_damage;
										}
										mass_for_me[i1].mana -= 25;
										if (mass_for_enemy[i2].health - mass_for_me[i1].special_damage < 0) {
											mass_for_enemy[i2].health = 0;
										}
										player_for_fight = 2;
										pos_y = 430;
									}
								}
								DrawTextureRec(texWave, frameRec, currentPos_for_wave, WHITE);
							}
							else {
								if (currentPos2_for_wave.x > endPos2_for_wave.x) {
									currentPos2_for_wave.x -= 20;
									if (currentPos2_for_wave.x <= endPos2_for_wave.x) {
										currentPos2_for_wave = endPos2_for_wave;
										isPlaying = false;
										if (mass_for_enemy[i1].weakness == mass_for_me[i2].element) {
											mass_for_enemy[i1].health -= int(mass_for_me[i2].special_damage * 1.2);
										}
										else {
											mass_for_enemy[i1].health -= mass_for_me[i2].special_damage;
										}
										mass_for_me[i2].mana -= 25;
										if (mass_for_enemy[i1].health - mass_for_me[i2].special_damage < 0) {
											mass_for_enemy[i1].health = 0;
										}
										player_for_fight = 1;
										pos_y = 430;
									}
								}
								DrawTextureRec(texWave2, frameRec2, currentPos2_for_wave, WHITE);
							}
						}
						break;
					}
				}
			}

			if (!position_changed && pos_y == 630) {
				string message5 = "Mana +10";
				DrawTextEx(font, message5.c_str(), { 900, 900 }, 80, 0, BLACK);
				if (mass_for_me[i].mana - 10 < 0) {
					if (IsKeyPressed(KEY_DOWN)) {
						pos_y += 100;
						position_changed = true;
					}
					if (IsKeyPressed(KEY_SPACE)) {
						if (mass_for_me[i].mana + 10 <= 100) {
							mass_for_me[i].mana += 10;
							if (player_for_fight == 1) player_for_fight = 2;
							else player_for_fight = 1;
							pos_y = 430;
						}
					}
				}
				else if (mass_for_me[i].mana - 25 < 0) {
					if (IsKeyPressed(KEY_UP)) {
						pos_y -= 200;
						position_changed = true;
					}
					if (IsKeyPressed(KEY_DOWN)) {
						pos_y += 100;
						position_changed = true;
					}
					if (IsKeyPressed(KEY_SPACE)) {
						if (mass_for_me[i].mana + 10 <= 100) {
							mass_for_me[i].mana += 10;
							if (player_for_fight == 1) player_for_fight = 2;
							else player_for_fight = 1;
							pos_y = 430;
						}
					}
				}
				else {
					if (!position_changed && IsKeyPressed(KEY_UP)) {
						pos_y -= 100;
						position_changed = true;
					}
					if (IsKeyPressed(KEY_DOWN)) {
						pos_y += 100;
						position_changed = true;
					}
					if (IsKeyPressed(KEY_SPACE)) {
						if (mass_for_me[i].mana + 10 <= 100) {
							mass_for_me[i].mana += 10;
							if (player_for_fight == 1) player_for_fight = 2;
							else player_for_fight = 1;
							pos_y = 430;
						}
					}
				}
			}

			if (!position_changed && pos_y == 730) {
				if (IsKeyPressed(KEY_UP)) {
					pos_y -= 100;
					position_changed = true;
				}
				if (IsKeyPressed(KEY_SPACE)) {
					if (!show) {
						vec.clear();
						for (int j = 0; j < mass_for_me.size(); j++) {
							if (j != i) {
								vec.push_back(j);
							}
						}
					}
					show = true;
				}
			}
			if (show && !position_changed) {
				if (pos_y == 730) {
					if (IsKeyPressed(KEY_DOWN)) {
						pos_y += 80;
						position_changed = true;
					}
					if (IsKeyPressed(KEY_UP)) {
						pos_y -= 80;
						position_changed = true;
					}
				}
				else if (pos_y == 810) {
					if (IsKeyPressed(KEY_DOWN)) {
						pos_y += 60;
						position_changed = true;
					}
					if (IsKeyPressed(KEY_UP)) {
						pos_y -= 80;
						position_changed = true;
					}
					if (player_for_fight == 1) {
						if (IsKeyPressed(KEY_SPACE)) {
							int temp = i1;
							i1 = vec[0];
							vec[0] = temp;
							show = false;
							pos_y = 430;
						}
					}
					else {
						if (IsKeyPressed(KEY_SPACE)) {
							int temp = i2;
							i2 = vec[0];
							vec[0] = temp;
							show = false;
							pos_y = 430;
						}
					}
				}
				else if (pos_y == 870) {
					if (IsKeyPressed(KEY_UP)) {
						pos_y -= 60;
						position_changed = true;
					}
					if (player_for_fight == 1) {
						if (IsKeyPressed(KEY_SPACE)) {
							int temp = i1;
							i1 = vec[1];
							vec[1] = temp;
							show = false;
							pos_y = 430;
						}
					}
					else {
						if (IsKeyPressed(KEY_SPACE)) {
							int temp = i2;
							i2 = vec[1];
							vec[1] = temp;
							show = false;
							pos_y = 430;
						}
					}
				}
			}
			if (!position_changed && (pos_y == 810 || pos_y == 870) && show) {
				if (show) {
					string messge = mass_for_me[vec[0]].name + " " + to_string(mass_for_me[vec[0]].health);
					DrawTextEx(font, messge.c_str(), Vector2{ 850, 920 }, 50, 0, BLACK);
					string messge1 = mass_for_me[vec[1]].name + " " + to_string(mass_for_me[vec[1]].health);
					DrawTextEx(font, messge1.c_str(), Vector2{ 850, 990 }, 50, 0, BLACK);
				}
			}
			if (player_for_fight == 1) {
				if (mass_for_me.size() == 1 && mass_for_me[i1].health == 0) {
					DrawTextEx(font, "Player 2 win", Vector2{ 700, 1100 }, 150, 0, BLACK);
				}
				else if (mass_for_enemy.size() == 1 && mass_for_enemy[i2].health == 0) {
					DrawTextEx(font, "Player 1 win", Vector2{ 700, 1100 }, 150, 0, BLACK);
				}
			}
			else {
				if (mass_for_me.size() == 1 && mass_for_me[i2].health == 0) {
					DrawTextEx(font, "Player 2 win", Vector2{ 700, 1100 }, 150, 0, BLACK);
				}
				else if (mass_for_enemy.size() == 1 && mass_for_enemy[i1].health == 0) {
					DrawTextEx(font, "Player 1 win", Vector2{ 700, 1100 }, 150, 0, BLACK);
				}
			}
		}
	}
}


Vector2 get_mouse_pos() {
	Vector2 pos = GetMousePosition();
	pos.x = pos.x / (float)GetScreenWidth() * 2160.0f;
	pos.y = pos.y / (float)GetScreenHeight() * 1370.0f;
	return pos;
}
