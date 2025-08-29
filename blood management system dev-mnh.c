#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

#ifdef _WIN32
#include <windows.h>
#endif

#define MAX_DONORS 100
#define STR_SMALL  32
#define STR_MED    64
#define STR_BIG    128

typedef struct {
    char name[STR_MED];
    char blood[STR_SMALL];
    char phone[STR_MED];
    char area[STR_MED];
} Donor;

typedef struct {
    char email[STR_BIG];
    char password[STR_BIG];
    int isAuroniX;
} User;


void trim_newline(char *s){
    size_t n = strlen(s);
    if(n && (s[n-1] == '\n' || s[n-1] == '\r')) s[n-1] = '\0';
}

void to_upper(char *s){
    for(; *s; ++s) *s = (char)toupper((unsigned char)*s);
}

void normalize_blood(char *s){
    for(; *s; ++s){
        if(*s == '0') *s = 'O';
        else *s = (char)toupper((unsigned char)*s);
    }
}

int iequals(const char *a, const char *b){
    for(; *a && *b; a++, b++){
        char ca = (char)toupper((unsigned char)*a);
        char cb = (char)toupper((unsigned char)*b);
        if(ca != cb) return 0;
    }
    return *a == '\0' && *b == '\0';
}

void load_donors(Donor donors[], int *count){
    *count = 0;
    // Helper macro
    #define ADD(name_, blood_, phone_, area_) do{ \
        strncpy(donors[*count].name,  (name_),  STR_MED-1); donors[*count].name[STR_MED-1]='\0'; \
        strncpy(donors[*count].blood, (blood_), STR_SMALL-1); donors[*count].blood[STR_SMALL-1]='\0'; \
        strncpy(donors[*count].phone, (phone_), STR_MED-1); donors[*count].phone[STR_MED-1]='\0'; \
        strncpy(donors[*count].area,  (area_),  STR_MED-1); donors[*count].area[STR_MED-1]='\0'; \
 \
        normalize_blood(donors[*count].blood); \
        (*count)++; \
    } while(0)

    // Dhanmondi
    ADD("Abdur Rahman","A+","8801714214531","Dhanmondi");
    ADD("Abu Saleh","A+","8801812345678","Dhanmondi");
    ADD("Ahasan","A+","8801918765432","Dhanmondi");
    ADD("Ahmed","B+","8801312345670","Dhanmondi");
    ADD("Ali","O+","8801419876543","Dhanmondi");
    ADD("Al-Amin","AB+","8801511122233","Dhanmondi");
    ADD("Ashik","A-","8801612349876","Dhanmondi");
    ADD("Azad","AB-","8801715566778","Dhanmondi");
    ADD("Babul","A+","8801819988776","Dhanmondi");
    ADD("Badal","O-","8801912233445","Dhanmondi");
    ADD("Badrul","B+","8801310099887","Dhanmondi");
    ADD("Bappy","AB+","8801416655443","Dhanmondi");
    ADD("Basir","A-","8801512233449","Dhanmondi");
    ADD("Chanchal","A-","8801612345671","Dhanmondi");
    ADD("Delwar","B","8801719988775","Dhanmondi");
    ADD("Elias","A-","8801811122334","Dhanmondi");
    ADD("Farhad","AB+","8801914455667","Dhanmondi");
    ADD("Faisal","O+","8801312233448","Dhanmondi");
    ADD("Gias","O-","8801410099886","Dhanmondi");
    ADD("Habib","A+","8801513344556","Dhanmondi");

    // Gulshan
    ADD("Hakim","A+","8801615566772","Gulshan");
    ADD("Hasan","A-","8801711122446","Gulshan");
    ADD("Imran","AB-","8801816677889","Gulshan");
    ADD("Islam","A+","8801915566771","Gulshan");
    ADD("Jakir","B+","8801314455668","Gulshan");
    ADD("Jewel","AB+","8801412233447","Gulshan");
    ADD("Kamal","A+","8801514455669","Gulshan");
    ADD("Kawsar","B+","8801616677885","Gulshan");
    ADD("Khan","B+","8801713344557","Gulshan");
    ADD("Liton","AB+","8801817788990","Gulshan");
    ADD("Mahbub","A-","8801917788991","Gulshan");
    ADD("Majid","A-","8801315566779","Gulshan");
    ADD("Mamun","AB+","8801413344558","Gulshan");
    ADD("Masud","AB+","8801515566773","Gulshan");
    ADD("Milon","AB+","8801617788992","Gulshan");
    ADD("Miraz","AB+","8801714455660","Gulshan");
    ADD("Mizan","AB+","8801818899001","Gulshan");
    ADD("Mohammad","AB+","8801918899002","Gulshan");
    ADD("Monir","AB-","8801316677884","Gulshan");
    ADD("Motaleb","AB+","8801414455661","Gulshan");
    ADD("Mukul","A+","8801516677886","Gulshan");

    // Uttara
    ADD("Munna","AB+","8801618899003","Uttara");
    ADD("Nasir","AB+","8801715566774","Uttara");
    ADD("Niaz","AB-","8801819900112","Uttara");
    ADD("Omar","B+","8801919900113","Uttara");
    ADD("Parvez","AB+","8801317788995","Uttara");
    ADD("Rafiq","A+","8801415566775","Uttara");
    ADD("Rahim","AB","8801517788994","Uttara");
    ADD("Rakib","AB-","8801619900114","Uttara");
    ADD("Rashed","A+","8801716677887","Uttara");
    ADD("Afrin","AB+","8801810011223","Uttara");
    ADD("Afroza","AB+","8801910011224","Uttara");
    ADD("Alia","O+","8801318899006","Uttara");
    ADD("Anika","A+","8801416677888","Uttara");
    ADD("Asma","B+","8801518899007","Uttara");
    ADD("Begum","A+","8801610011225","Uttara");
    ADD("Bristi","AB+","8801717788996","Uttara");
    ADD("Champa","AB+","8801811122335","Uttara");
    ADD("Fatema","AB+","8801911122336","Uttara");
    ADD("Farida","AB+","8801319900117","Uttara");
    ADD("Halima","AB+","8801417788997","Uttara");

    // Baridhara
    ADD("Hena","A+","8801519900118","Baridhara");
    ADD("Hosna","AB-","8801611122337","Baridhara");
    ADD("Humaira","AB+","8801718899008","Baridhara");
    ADD("Iffat","A-","8801812233446","Baridhara");
    ADD("Jahan","A-","8801912233447","Baridhara");
    ADD("Jannat","AB-","8801310011228","Baridhara");
    ADD("Jharna","A+","8801418899009","Baridhara");
    ADD("Khadija","A+","8801510011229","Baridhara");
    ADD("Lima","B-","8801612233440","Baridhara");
    ADD("Mahfuza","O+","8801719900110","Baridhara");
    ADD("Maimuna","AB+","8801813344559","Baridhara");
    ADD("Marufa","O-","8801913344560","Baridhara");
    ADD("Minu","AB-","8801311122339","Baridhara");
    ADD("Munni","AB+","8801419900111","Baridhara");
    ADD("Nasrin","B+","8801511122340","Baridhara");
    ADD("Nazma","A-","8801613344561","Baridhara");
    ADD("Nipa","A-","8801710011226","Baridhara");
    ADD("Nusrat","A-","8801814455662","Baridhara");
    ADD("Parvin","AB+","8801914455663","Baridhara");
    ADD("Rehana","A+","8801312233441","Baridhara");
    ADD("Rina","AB+","8801410011227","Baridhara");

    // Banani
    ADD("Rumana","AB+","8801512233442","Banani");
    ADD("Rupa","AB+","8801614455664","Banani");
    ADD("Sabina","AB-","8801711122338","Banani");
    ADD("Sadia","AB-","8801815566776","Banani");
    ADD("Saima","A-","8801915566777","Banani");
    ADD("Salma","AB+","8801313344550","Banani");
    ADD("Samira","A+","8801411122330","Banani");
    ADD("Sanjida","B+","8801513344551","Banani");
    ADD("Shathi","AB+","8801615566778","Banani");
    ADD("Shima","B-","8801712233443","Banani");
    ADD("Shumi","AB+","8801816677880","Banani");
    ADD("Sumaiya","B+","8801916677881","Banani");
    ADD("Taslima","A+","8801314455665","Banani");
    ADD("Tisha","AB-","8801412233444","Banani");
    ADD("Urmi","B+","8801514455666","Banani");
    ADD("Yasmin","A-","8801616677882","Banani");
    ADD("Zannat","AB-","8801714455669","Banani");
    ADD("Zeenat","A+","8801684485634","Banani");

    #undef ADD
}

// ---------- Search ----------
void show_donor(const Donor *d, int idx){
    printf("%2d) %-15s | %-3s | %s | %s\n", idx, d->name, d->blood, d->phone, d->area);
}

int search_by_blood_and_area(Donor donors[], int n, const char *blood, const char *area){
    int found = 0, shown = 0;
    for(int i=0;i<n;i++){
        if(iequals(donors[i].blood, blood) && iequals(donors[i].area, area)){
            show_donor(&donors[i], ++shown);
            found = 1;
        }
    }
    if(!found) printf("No matches found.\n");
    return shown;
}

int search_by_blood(Donor donors[], int n, const char *blood){
    int found = 0, shown = 0;
    for(int i=0;i<n;i++){
        if(iequals(donors[i].blood, blood)){
            show_donor(&donors[i], ++shown);
            found = 1;
        }
    }
    if(!found) printf("No matches found.\n");
    return shown;
}

int search_by_area(Donor donors[], int n, const char *area){
    int found = 0, shown = 0;
    for(int i=0;i<n;i++){
        if(iequals(donors[i].area, area)){
            show_donor(&donors[i], ++shown);
            found = 1;
        }
    }
    if(!found) printf("No matches found.\n");
    return shown;
}

void show_menu(){
    printf("\n--- MENU ---\n");
    printf("(1) Post blood request\n");
    printf("(2) Donor matching\n");
    printf("(3) Donor search\n");
    printf("(4) Notification\n");
    printf("(5) Donation History\n");
    printf("(6) Log-out\n");
    printf("Choose (1-6): ");
}


void welcome_screen(const User *u){
    if(u->isAuroniX){
        printf("\nWelcome AURONIX\n");
        printf("O- blood\n");
    } else {
        printf("\nWelcome %s\n", u->email);
    }
}

void post_blood_request(Donor donors[], int n){
    char blood[STR_SMALL], area[STR_MED];

    printf("\nEnter blood group: ");
    fgets(blood, sizeof(blood), stdin); trim_newline(blood);
    normalize_blood(blood);

    printf("Enter area: ");
    fgets(area, sizeof(area), stdin); trim_newline(area);

    printf("\n--- Results (Blood: %s, Area: %s) ---\n", blood, area);
    search_by_blood_and_area(donors, n, blood, area);
}

void donor_matching(Donor donors[], int n){
    char blood[STR_SMALL];

    printf("\nEnter desired blood group: ");
    fgets(blood, sizeof(blood), stdin); trim_newline(blood);
    normalize_blood(blood);

    printf("\n--- Results (Blood: %s) ---\n", blood);
    search_by_blood(donors, n, blood);
}

void donor_search(Donor donors[], int n){
    char area[STR_MED];

    printf("\nEnter desired area: ");
    fgets(area, sizeof(area), stdin); trim_newline(area);

    printf("\n--- Results (Area: %s) ---\n", area);
    search_by_area(donors, n, area);
}

void notification(const User *u){
    printf("\n--- Notification ---\n");
    if(u->isAuroniX){
        printf("You saved 1 people in Milestone Tragedy\n");
    } else {
        printf("No notification\n");
    }
}

void donation_history(const User *u){
    printf("\n--- Donation History ---\n");
    if(u->isAuroniX){
        printf("You donated blood at 21 July 2025 at Dhanmondi\n");
    } else {
        printf("There are no donation history of yours\n");
    }
}

int is_special_account(const char *email, const char *password){
    return iequals(email, "team.auronix@gmail.com") && strcmp(password, "AuRoNiX5") == 0;
}

void register_user(User *u){
    char email[STR_BIG], pass[STR_BIG];

    printf("\n--- Registration ---\n");
    printf("Email: ");
    fgets(email, sizeof(email), stdin); trim_newline(email);

    printf("Password: ");
    fgets(pass, sizeof(pass), stdin); trim_newline(pass);

    strncpy(u->email, email, STR_BIG-1); u->email[STR_BIG-1]='\0';
    strncpy(u->password, pass, STR_BIG-1); u->password[STR_BIG-1]='\0';
    u->isAuroniX = is_special_account(u->email, u->password);

    printf("\nRegistration successful. You are now logged in.\n");
}

int login_user(User *u){
    char email[STR_BIG], pass[STR_BIG];

    printf("\n--- Login ---\n");
    printf("Email: ");
    fgets(email, sizeof(email), stdin); trim_newline(email);

    printf("Password: ");
    fgets(pass, sizeof(pass), stdin); trim_newline(pass);

    strncpy(u->email, email, STR_BIG-1); u->email[STR_BIG-1]='\0';
    strncpy(u->password, pass, STR_BIG-1); u->password[STR_BIG-1]='\0';
    u->isAuroniX = is_special_account(u->email, u->password);

    printf("\nLogin successful.\n");
    return 1;
}

int auth_screen(User *u){
    while(1){
        printf("\n=== Blood Donation & Emergency Matching System ===\n");
        printf("1) Register\n");
        printf("2) Login\n");
        printf("0) Exit\n");
        printf("Choose: ");

        char buf[STR_SMALL];
        if(!fgets(buf, sizeof(buf), stdin)) return 0;
        int choice = atoi(buf);

        if(choice == 1){
            register_user(u);
            return 1;
        } else if(choice == 2){
            if(login_user(u)) return 1;
        } else if(choice == 0){
            return 0;
        } else {
            printf("Invalid choice. Try again.\n");
        }
    }
}

int main(void){
    #ifdef _WIN32
    #endif
    Donor donors[MAX_DONORS];
    int nDonors = 0;
    load_donors(donors, &nDonors);
    while(1){
        User user = {0};
        if(!auth_screen(&user)){
            printf("\nGoodbye!\n");
            printf("\nDeveloped by: MD. NAZMUL HASAN\n");
            break;
        }
        welcome_screen(&user);
        while(1){
            show_menu();
            char buf[STR_SMALL];
            if(!fgets(buf, sizeof(buf), stdin)) { puts("\nInput ended."); return 0; }
            int choice = atoi(buf);
            switch(choice){
                case 1: post_blood_request(donors, nDonors); break;
                case 2: donor_matching(donors, nDonors); break;
                case 3: donor_search(donors, nDonors); break;
                case 4: notification(&user); break;
                case 5: donation_history(&user); break;
                case 6:
                    printf("\nLogged out.\n");
                    goto DO_LOGOUT;
                default:
                    printf("Invalid option. Please choose 1-6.\n");
            }
        }
        DO_LOGOUT:
        ;
    }
    return 0;
}
