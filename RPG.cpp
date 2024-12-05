#include <iostream>
#include <vector>
#include <ctime>

using namespace std;

//bleed = 15 to enemies * stacks, 10 to player / turn
//regen(bandage) = 10 to enemies / turn, 15 to player/ turn
//fortitude = 25% dmg increase / turn



//function prototypes list
string select_opponent();
void enemy_hp_list_add();
void enemy_name_list_add();
void enemy_stats_setup();
void select_your_abilities();
void player_abilities_list_add();
void ability_effect_list(string);
void player_attack_trigger();
void show_enemy_and_player_hp();
void enemy_attack_AI();
void buffs_debuffs_effect();
int check_victory();



// global data scope, for general stats and data
double player_hp=100, enemy_hp;
string enemy_name;
vector <string> name_list;
vector <int> hp_list;
vector <string> abilities_list;
vector <string> active_abilities_list;
int is_enemy_bleeding=0, is_player_fortitude=0, is_player_bandage=0,is_player_bleeding=0,is_enemy_bandage=0;
int enemy_used_ult=0;


//lets the player select an attack from the active_abilities_list vector
void player_attack_trigger()
{
    int selecting_ability_to_use;
    cout<<"\nChoose an Ability to use: (type in numbers)\n\n";
    for(int i=0; i<size(active_abilities_list); i++)
    {
        cout<<i+1<<" ."<<active_abilities_list.at(i)<<'\n';
    }
    cout<<'\n';
    while(true)
    {
        cin>>selecting_ability_to_use;
        if (selecting_ability_to_use<=size(active_abilities_list) && selecting_ability_to_use>=1)
        {
            ability_effect_list(active_abilities_list.at(selecting_ability_to_use-1));
            break;
        }
        else
        {
            cout<<"\nAbility invalid.. Try Again\n\n";
        }
    }
}



//outsorces abilities effects in the search function
void ability_effect_list(string ability)
{
    if (ability == "Strike!")
    {
        if(is_player_fortitude>0)
        {
            cout<<"\n\n---You used Strike! Your opponent loses "<<50*1.25<<" HitPoints.---\n\n";
            enemy_hp-=50*1.25;
        }
        else
        {
            cout<<"\n\n---You used Strike! Your opponent loses 50 HitPoints.---\n\n";
            enemy_hp-=50;
        }
    }
    if (ability == "Throw")
    {
        if(is_player_fortitude>0)
        {
            cout<<"\n\n---Your used Throw. You attack swiftly for "<<30*1.25<<" HitPoints and bleed your opponent for one turn.---\n\n";
            enemy_hp-=30*1.25;
        }
        else
        {
            cout<<"\n\n---Your used Throw. You attack swiftly for 30 HitPoints and bleed your opponent for one turn.---\n\n";
            enemy_hp-=30;
        }
        is_enemy_bleeding+=1;
    }
    if (ability == "Slam!")
    {


        //nu inteleg cum functioneaza dar cout<<result%10 face nr random de la 0 la 9 in functie de timpul petrecut
        time_t result = time(nullptr);


        //crit chance
        if (result%2==0)
        {
            //crit fail
            if(is_player_fortitude>0)
            {
                cout<<"\n\n---You Slamed! Your target is hit and loses "<<35*1.25<<" HitPoints.---\n\n";
                enemy_hp-=35*1.25;
            }
            else
            {
                cout<<"\n\n---You Slamed! Your target is hit and loses 35 HitPoints.---\n\n";
                enemy_hp-=35;
            }
        }
        else
        {
            //crit success
            if(is_player_fortitude>0)
            {
                cout<<"\n\n---You Slamed! You CRITICALLY hit your enemy, causing "<<70*1.25<<" HitPoints to drop---!!!\n\n";
                enemy_hp-=70*1.25;
            }
            else
            {
                cout<<"\n\n---You Slamed! You CRITICALLY hit your enemy, causing 70 HitPoints to drop---!!!\n\n";
                enemy_hp-=70;
            }
        }

    }
    if (ability == "Fortitude")
    {
        cout<<"\n\n---You used Fortitude. gaining 25% damage increase for 3 rounds.---\n\n";
        is_player_fortitude+=3;
    }
    if (ability == "Wound")
    {
        cout<<"\n\n---You used Wound. Bleeding your opponent for 2 turns.---\n\n";
        is_enemy_bleeding+=2;
    }
    if (ability == "Bandage")
    {
        cout<<"\n\n---You used Bandage. Healing yourself for 3 turns.---\n\n";
        is_player_bandage+=3;
    }
}



//this serves as a menu for selecting different abilities to the vector(max 4)
void select_your_abilities()
{
    vector <int> abilities_chosen_yet(4);
    cout<<"\nChoose your abilities: (type in numbers)\n\n";
    int add;
    cout<<'\n';
    for(int i=0; i<size(abilities_list); i++)
    {
        cout<<i+1<<" ."<<abilities_list.at(i)<<'\n';
    }
    cout<<"\n\nWhich 4 abilities do you want to have?\n\n";
    for (int i=0; i<4; i++)
    {
        while(true)
        {
            cin>>add;
            //chosen abilities yet verifies if the ability has been chosen before as to not get 4 x strike!
            if ((add<=size(abilities_list) && add>=1) && (abilities_chosen_yet.at(0)!=add && abilities_chosen_yet.at(1)!=add && abilities_chosen_yet.at(2)!=add && abilities_chosen_yet.at(3)!=add))
            {
                active_abilities_list.push_back(abilities_list.at(add-1));
                abilities_chosen_yet.at(i)=add;
                break;
            }
            else
            {
                cout<<"\nAbility invalid.. Try Again\n\n";
            }
        }
    }
}



//this adds all of the abilities to a vector containing all of them
void player_abilities_list_add()
{
    abilities_list.push_back("Strike!"); //Dmg No chance to crit, deals 50
    abilities_list.push_back("Throw"); //Dmg no chance to crit, deals 30, adds 1 stack of bleed to the enemy
    abilities_list.push_back("Slam!"); //Dmg 50% chance to crit, deals 35, crti deals 70
    abilities_list.push_back("Fortitude"); //Buff buffs damage dealt by 25%
    abilities_list.push_back("Wound"); //DoT 15 * stack / 2 (stacks) turns
    abilities_list.push_back("Bandage"); //HoT heals 15 / turn
}



//insert enemy names in the list
void enemy_name_list_add()
{
    name_list.push_back("Grasshopper");
}



//insert enemy hp in list
void enemy_hp_list_add()
{
    hp_list.push_back(100);
}



//select and display opponent function
int select_display_opponent()
{
    int i=0;
    cout<<"\nSelect Your Opponent:\n\n";
    for (auto single_enemy: name_list)
    {
        i++;
        cout<<i<<". "<<single_enemy<<'\n';
    }
    unsigned int selector;
    cout<<"\nWhich Enemy do you want to fight? (type in numbers)\n\n";
    while(true)
    {
        cin>>selector;
        if (selector<=size(name_list) && selector>=1)
        {
            return selector-1;
        }
        else
        {
            cout<<"You did not select a valid enemy, type again";
        }
    }
}



//used to select the enemy and set it's stats for the console
void enemy_stats_setup()
{
    int selector;
    //aux = place holder for enemy value
    int aux=select_display_opponent();

    enemy_hp=hp_list.at(aux);
    enemy_name=name_list.at(aux);
    cout<<"\nYour opponent will be: "<<enemy_name<<"\n\n";
}



//used for the AI of the enemies
void enemy_attack_AI()
{
    //random attacks generator (oscilates)
    time_t result = time(nullptr);

    //attack AI for Grasshopper
    if(enemy_name=="Grasshopper")
    {
        if(enemy_hp<30 && enemy_used_ult==0)
        {
            cout<<"\nGrasshopper is agitated. He uses grass baldes to cut you, dealing 25 dmg and bleeding you for one round.\n\n";
            player_hp-=25;
            enemy_used_ult=1;
            is_player_bleeding+=1;
            return;
        }
        if(result%2==0)
        {
            cout<<"\nGrasshopper used Jump Kick. Dealing 15 HealthPoints to you.\n\n";
            player_hp-=15;
        }
        else
        {
            cout<<"\nGrasshopper used Sing. Healing himself for 10\n\n";
            if (enemy_hp+10>100)
            {
                //if hp is above max
                enemy_hp=100;
            }
            else
            {
                //if hp in under max
                enemy_hp+=10;
            }
        }
    }
}



//checks for buffs and debuffs and applies them to both parties
void buffs_debuffs_effect()
{
    if(is_enemy_bleeding==0 && is_player_fortitude==0 && is_player_bandage==0 && is_player_bleeding==0 && is_enemy_bandage==0)
    {
        return;
    }
    cout<<"\n---------Buffs and Debuffs----------";
    //player buffs debuffs
    if(is_player_bandage>0)
    {
        //bandage healing
        cout<<"\nPlayer has been healed by Bandage for 15 HitPoints";
        if(player_hp+10>100)
        {
            player_hp=100;
        }
        else
        {
            player_hp+=15;
        }
        is_player_bandage--;
    }
    if(is_player_bleeding>0)
    {
        //bleeding
        cout<<"\nPlayer Bleeds and loses 15 HitPoints";
        player_hp+=15;
        is_player_bleeding--;
    }
    if(is_player_fortitude>0)
    {
        //fortitude buffing
        is_player_fortitude--;
        if(is_player_fortitude==0)
        {
            cout<<"\nPlayer has lost Fortitude buff";
        }
    }



    //enemy buffs/debuffs
    if(is_enemy_bandage>0)
    {
        cout<<"\nEnemy heals for 10 HitPoints";
        if (enemy_hp+10>100)
        {
            //if hp is above max
            enemy_hp=100;
            is_enemy_bandage--;
        }
        else
        {
            //if hp in under max
            enemy_hp+=10;
            is_enemy_bandage--;
        }
    }
    if (is_enemy_bleeding>0)
    {
        cout<<"\nEnemy loses "<<15*is_enemy_bleeding<<" HitPoints from Bleed";
        enemy_hp-=15*is_enemy_bleeding;
        is_enemy_bleeding--;
    }
    cout<<"\n------------------------------------\n\n";

}



//used for checking victory for both parties
int check_victory()
{
    if (player_hp<=0)
    {
        //player has lost
        cout<<"--------Enemy has won!!!--------";
        return 1;
    }
    else if (enemy_hp<=0)
    {
        //enemy has been defeated
        cout<<"--------Player has won!!!--------";
        return 2;
    }
    else
    {
        //nobody won yet
        return 0;
    }
}



//used for showing both hps
void show_enemy_and_player_hp()
{
    cout<<"\n\nEnemy's Health:"<<enemy_hp<<'\n';
    cout<<"\n\nPLayer's Health:"<<player_hp<<"\n\n";
}



//runs the game and commands for game
int main()
{
    cout<<"Welcome to Daisferry's PokemonStyle RPG\n\n";

    //adding names , hp, abilities to list
    enemy_name_list_add();
    enemy_hp_list_add();
    player_abilities_list_add();

    //setting up opponent and stats from list mentioned above
    enemy_stats_setup();

    //adding player abilities to list and selecting active ones for fight
    select_your_abilities();

    cout<<"\n\n----------The Match Begins!!!----------\n\n";

    //attack phase
    while(true)
    {
        //player attack
        player_attack_trigger();
        //victory check
        if (check_victory()!=0)
        {
            break;
        }
        //enemy attack
        enemy_attack_AI();
        //victory check
        if (check_victory()!=0)
        {
            break;
        }
        show_enemy_and_player_hp();
        //buffs and debuffs applied
        buffs_debuffs_effect();
        //victory check
        if (check_victory()!=0)
        {
            break;
        }
    }

    return 0;
}
