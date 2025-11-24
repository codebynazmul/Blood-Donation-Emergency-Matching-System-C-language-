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
#define USER_FILE "users.dat"

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

// ---------- Utility Functions ----------
void trim_newline(char *s){
    size_t n = strlen(s);
    if(n && (s[n-1] == '\n' || s[n-1] == '\r')) s[n-1] = '\0';
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

// ---------- Donor Database ----------
void load_donors(Donor donors[], int *count){
    *count = 0;
    #define ADD(name_, blood_, phone_, area_) do{ \
        strncpy(donors[*count].name,  (name_),  STR_MED-1); donors[*count].name[STR_MED-1]='\0'; \
        strncpy(donors[*count].blood, (blood_), STR_SMALL-1); donors[*count].blood[STR_SMALL-1]='\0'; \
        strncpy(donors[*count].phone, (phone_), STR_MED-1); donors[*count].phone[STR_MED-1]='\0'; \
        strncpy(donors[*count].area,  (area_),  STR_MED-1); donors[*count].area[STR_MED-1]='\0'; \
        normalize_blood(donors[*count].blood); \
        (*count)++; \
    } while(0)

    // Example donors (Add your full list here)
    ADD("Abdur Rahman","A+","8801714214531","Dhanmondi");
    ADD("Hakim","A+","8801615566772","Gulshan");
    ADD("Munna","AB+","8801618899003","Uttara");
    ADD("Hena","A+","8801519900118","Baridhara");
    ADD("Rumana","AB+","8801512233442","Banani");

    #undef ADD
}

// ---------- Donor Search ----------
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

// ---------- Menu ----------
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

// ---------- User Interface ----------
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

// ---------- Email Validation ----------
int is_valid_email(const char *email){
    const char *at = strchr(email, '@');
    if(!at || at == email) return 0;
    const char *dot = strchr(at, '.');
    if(!dot || dot == at + 1) return 0;
    return 1;
}

// ---------- File Handling ----------
int save_user(const User *u){
    FILE *fp = fopen(USER_FILE, "a");
    if(!fp) return 0;
    fprintf(fp, "%s %s\n", u->email, u->password);
    fclose(fp);
    return 1;
}

int check_user(const char *email, const char *password){
    FILE *fp = fopen(USER_FILE, "r");
    if(!fp) return 0;
    char file_email[STR_BIG], file_pass[STR_BIG];
    int found = 0;
    while(fscanf(fp, "%s %s", file_email, file_pass) == 2){
        if(strcmp(email, file_email) == 0 && strcmp(password, file_pass) == 0){
            found = 1;
            break;
        }
    }
    fclose(fp);
    return found;
}

int is_special_account(const char *email, const char *password){
    return iequals(email, "team.auronix@gmail.com") && strcmp(password, "AuRoNiX5") == 0;
}

// ---------- Auth ----------
void register_user(User *u){
    char email[STR_BIG], pass[STR_BIG];

    while(1){
        printf("\n--- Registration ---\n");
        printf("Email: ");
        fgets(email, sizeof(email), stdin); trim_newline(email);

        if(!is_valid_email(email)){
            printf("Invalid email format. Try again.\n");
            continue;
        }

        printf("Password: ");
        fgets(pass, sizeof(pass), stdin); trim_newline(pass);

        strncpy(u->email, email, STR_BIG-1); u->email[STR_BIG-1]='\0';
        strncpy(u->password, pass, STR_BIG-1); u->password[STR_BIG-1]='\0';
        u->isAuroniX = is_special_account(u->email, u->password);

        if(save_user(u)){
            printf("\nRegistration successful. You are now logged in.\n");
        } else {
            printf("Error saving user. Try again.\n");
        }
        break;
    }
}

int login_user(User *u){
    char email[STR_BIG], pass[STR_BIG];
    int attempts = 3;

    while(attempts--){
        printf("\n--- Login ---\n");
        printf("Email: ");
        fgets(email, sizeof(email), stdin); trim_newline(email);

        if(!is_valid_email(email)){
            printf("Invalid email format. Try again.\n");
            continue;
        }

        printf("Password: ");
        fgets(pass, sizeof(pass), stdin); trim_newline(pass);

        if(check_user(email, pass)){
            strncpy(u->email, email, STR_BIG-1); u->email[STR_BIG-1]='\0';
            strncpy(u->password, pass, STR_BIG-1); u->password[STR_BIG-1]='\0';
            u->isAuroniX = is_special_account(u->email, u->password);
            printf("\nLogin successful.\n");
            return 1;
        } else {
            printf("Incorrect email or password. Attempts left: %d\n", attempts);
        }
    }
    return 0;
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

// ---------- Main ----------
int main(void){
    Donor donors[MAX_DONORS];
    int nDonors = 0;
    load_donors(donors, &nDonors);

    while(1){
        User user = {0};
        if(!auth_screen(&user)){
            printf("\nGoodbye!\nDeveloped by: MD. NAZMUL HASAN\n");
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
