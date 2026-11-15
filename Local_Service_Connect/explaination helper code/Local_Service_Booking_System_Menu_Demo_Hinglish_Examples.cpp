#include <iostream>
#include <string>
using namespace std;

// ============================================================
// LOCAL SERVICE BOOKING SYSTEM - MENU + WORKING DEMONSTRATION
// Ye program menu navigation, example outputs aur data-structure
// working samjhane ke liye hai. Real account/booking save nahi hoti.
// ============================================================

string area_name(int choice)
{
    if (choice == 1) return "Rishikesh";
    if (choice == 2) return "Raipur";
    if (choice == 3) return "Dehradun";
    if (choice == 4) return "Clement Town";
    if (choice == 5) return "Prem Nagar";
    return "Unknown";
}

string service_name(int choice)
{
    if (choice == 1) return "Plumber";
    if (choice == 2) return "Carpenter";
    if (choice == 3) return "Electrician";
    if (choice == 4) return "Geyser Repair";
    if (choice == 5) return "AC Repair";
    if (choice == 6) return "Painter";
    if (choice == 7) return "Cleaner";
    if (choice == 8) return "Appliance Repair";
    if (choice == 9) return "Vegetable Vendor";
    return "Unknown";
}

int area_menu()
{
    int choice;
    while (1)
    {
        cout << "\n--- AREA CHOOSE KARO ---\n";
        cout << "1. Rishikesh\n2. Raipur\n3. Dehradun\n4. Clement Town\n5. Prem Nagar\n0. Back\n";
        cout << "Choice: ";
        cin >> choice;
        if (choice >= 1 && choice <= 5)
        {
            cout << "Selected area: " << area_name(choice) << "\n";
            cout << "Actual program mein ye area User/Provider object ke area field mein save hota hai.\n";
            return choice;
        }
        else if (choice == 0) return 0;
        else cout << "Invalid choice. Dobara try karo.\n";
    }
}

int service_menu()
{
    int choice;
    while (1)
    {
        cout << "\n--- SERVICE CHOOSE KARO ---\n";
        cout << "1. Plumber\n2. Carpenter\n3. Electrician\n4. Geyser Repair\n";
        cout << "5. AC Repair\n6. Painter\n7. Cleaner\n8. Appliance Repair\n9. Vegetable Vendor\n0. Back\n";
        cout << "Choice: ";
        cin >> choice;
        if (choice >= 1 && choice <= 9)
        {
            cout << "Selected service: " << service_name(choice) << "\n";
            cout << "Actual program mein isi service ko Provider ke service field se match kiya jata hai.\n";
            return choice;
        }
        else if (choice == 0) return 0;
        else cout << "Invalid choice. Dobara try karo.\n";
    }
}

void sign_up_user()
{
    int choice;
    cout << "\n--- USER SIGN UP ---\n";
    cout << "Actual program name, phone, email, password, area aur security answers leta hai.\n";
    cout << "1. Area choose karo\n0. Back\nChoice: ";
    cin >> choice;
    if (choice == 0) return;
    if (choice != 1)
    {
        cout << "Invalid choice.\n";
        return;
    }
    int area = area_menu();
    if (area == 0) return;

    cout << "\n--- EXAMPLE: USER SIGNUP KE BAAD ---\n";
    cout << "User ID       : 1\n";
    cout << "Name          : Aditi Sharma\n";
    cout << "Phone         : 9999900001\n";
    cout << "Email         : aditi@example.com\n";
    cout << "Area          : " << area_name(area) << "\n";
    cout << "Booking stacks: Active / Cancelled-Rejected / Completed (initially empty)\n";
    cout << "Actual working: constructor User object banata hai; User linked list ke END mein node add hota hai.\n";
    cout << "Next new user ko ID 2 milegi, phir 3, and so on.\n";
    cout << "Note: ye sample output hai; demo mode mein account save nahi hua.\n";
}

void sign_up_provider()
{
    int choice;
    cout << "\n--- PROVIDER SIGN UP ---\n";
    cout << "Actual program name, phone, email, password, service, area aur security answers leta hai.\n";
    cout << "1. Service aur area choose karo\n0. Back\nChoice: ";
    cin >> choice;
    if (choice == 0) return;
    if (choice != 1)
    {
        cout << "Invalid choice.\n";
        return;
    }
    int service = service_menu();
    if (service == 0) return;
    int area = area_menu();
    if (area == 0) return;

    cout << "\n--- EXAMPLE: PROVIDER SIGNUP KE BAAD ---\n";
    cout << "Provider ID   : 100\n";
    cout << "Name          : Ramesh Kumar\n";
    cout << "Phone         : 9999900100\n";
    cout << "Service       : " << service_name(service) << "\n";
    cout << "Area          : " << area_name(area) << "\n";
    cout << "Average rating: 4.60 (example)\nCompleted work: 28 (example)\n";
    cout << "Waiting queue, main queue aur completed-history stack Provider ke apne honge.\n";
    cout << "Actual working: Provider ID 100 se start; Provider object linked list ke END mein add hota hai.\n";
    cout << "Note: ye sample output hai; demo mode mein account save nahi hua.\n";
}

void sign_in_explanation(int user_side)
{
    cout << "\nActual sign-in ki working:\n";
    cout << "- Linked list traverse karke User/Provider ki ID, phone ya email search hoti hai.\n";
    cout << "- Match milne par password verify hota hai.\n";
    cout << "- current_access_user/current_access_provider matched object ka address rakhta hai.\n";
    cout << "- Password galat ho to security answers verify karke password recovery ki ja sakti hai.\n";
    if (user_side == 1)
    {
        cout << "Example: Aditi Sharma (User ID 1) login kare to User Dashboard open hoga.\n";
        cout << "Demo shortcut: login credentials verify nahi ho rahe; seedha dashboard explore kar sakte ho.\n";
    }
    else
    {
        cout << "Example: Ramesh Kumar (Provider ID 100) login kare to Provider Dashboard open hoga.\n";
        cout << "Demo shortcut: login credentials verify nahi ho rahe; seedha dashboard explore kar sakte ho.\n";
    }
}

void display_user_info()
{
    cout << "\n--- DISPLAY USER INFO: SAMPLE OUTPUT ---\n";
    cout << "User ID : 1\nName    : Aditi Sharma\nPhone   : 9999900001\n";
    cout << "Email   : aditi@example.com\nArea    : Dehradun\n";
    cout << "Ye example hai ki Display Info select karne par logged-in User ki details aise dikhengi.\n";
}

void change_user_info()
{
    cout << "\n--- CHANGE USER INFO: SAMPLE ---\n";
    cout << "Before: Name = Aditi Sharma, Area = Dehradun, Phone = 9999900001\n";
    cout << "User updated area to Rishikesh.\n";
    cout << "After : Name = Aditi Sharma, Area = Rishikesh, Phone = 9999900001\n";
    cout << "Actual program same User object ke profile fields update karta hai; User ID aur linked-list node same rehte hain.\n";
}

void display_provider_info()
{
    cout << "\n--- DISPLAY PROVIDER INFO: SAMPLE OUTPUT ---\n";
    cout << "Provider ID : 100\nName        : Ramesh Kumar\nPhone       : 9999900100\n";
    cout << "Service     : Electrician\nArea        : Dehradun\nAverage     : 4.60 / 5\nCompleted jobs: 28\n";
    cout << "Average rating total_rating / total_ratings_received se nikalti hai, work_count se nahi.\n";
}

void change_provider_info()
{
    cout << "\n--- CHANGE PROVIDER INFO: SAMPLE ---\n";
    cout << "Before: Ramesh Kumar | Service: Electrician | Area: Dehradun\n";
    cout << "Provider updates area to Raipur.\n";
    cout << "After : Ramesh Kumar | Service: Electrician | Area: Raipur\n";
    cout << "Provider ID aur existing booking history change nahi hoti.\n";
}

void create_booking()
{
    int choice;
    cout << "\n--- CREATE BOOKING ---\nPehle service aur area choose karo.\n";
    cout << "1. Service choose karo\n0. Back\nChoice: ";
    cin >> choice;
    if (choice == 0) return;
    if (choice != 1)
    {
        cout << "Invalid choice.\n";
        return;
    }
    int service = service_menu();
    if (service == 0) return;
    int area = area_menu();
    if (area == 0) return;

    cout << "\nSelected search: " << service_name(service) << " in " << area_name(area) << "\n";
    cout << "--- PROVIDER SORTING ---\n";
    cout << "1. Current linked-list order\n2. Highest rating first\n3. Highest completed work first\n0. Back\nChoice: ";
    cin >> choice;
    if (choice == 0) return;
    if (choice < 1 || choice > 3)
    {
        cout << "Invalid choice.\n";
        return;
    }
    if (choice == 1) cout << "Providers linked-list traversal order mein rahenge; sorting nahi hogi.\n";
    else if (choice == 2) cout << "Bubble sort average rating ko highest se lowest arrange karega.\n";
    else cout << "Bubble sort work_count ko highest se lowest arrange karega.\n";

    cout << "\n--- MATCHING PROVIDERS: EXAMPLE DISPLAY ---\n";
    cout << "Search filters: same service + same area + waiting queue mein space.\n";
    cout << "Example result 1: Provider ID 100 | Ramesh Kumar | " << service_name(service) << " | " << area_name(area) << " | Rating 4.60 | Jobs 28\n";
    cout << "Example result 2: Provider ID 101 | Mohan Singh | " << service_name(service) << " | " << area_name(area) << " | Rating 4.30 | Jobs 19\n";
    cout << "Jis Provider ki waiting queue full hai, use results mein include nahi karenge.\n";
    cout << "Search: first pass match count; exact size ka Provider** array allocate; second pass results fill; end mein delete[].\n";
    cout << "1. Provider ID 100 choose karo\n2. Provider ID 101 choose karo\n0. Cancel\nChoice: ";
    cin >> choice;
    if (choice == 0)
    {
        cout << "Booking cancel kar di; booking object create nahi hua.\n";
        return;
    }
    if (choice != 1 && choice != 2)
    {
        cout << "Invalid provider choice.\n";
        return;
    }

    int provider_id = 100;
    string provider_name = "Ramesh Kumar";
    if (choice == 2)
    {
        provider_id = 101;
        provider_name = "Mohan Singh";
    }
    cout << "\n--- BOOKING CREATED: EXAMPLE DATA MOVEMENT ---\n";
    cout << "Booking number : 1000\nUser           : Aditi Sharma (ID 1)\n";
    cout << "Provider       : " << provider_name << " (ID " << provider_id << ")\n";
    cout << "Service / Area : " << service_name(service) << " / " << area_name(area) << "\nStatus         : WAITING\n";
    cout << "1. Ek Booking object create hota hai; booking numbers 1000 se start hote hain.\n";
    cout << "2. Usi Booking* ko User ke active-booking stack par PUSH karte hain.\n";
    cout << "3. Wahi Booking* Provider ki waiting circular queue ke REAR par ENQUEUE hota hai.\n";
    cout << "Isliye User aur Provider dono same Booking record ko refer karte hain; duplicate object nahi banta.\n";
    cout << "Ye illustrative output hai; demo mein booking actually save nahi hui.\n";
}

void cancel_booking()
{
    int number;
    cout << "\n--- CANCEL BOOKING ---\n";
    cout << "Example active list: #1002 WAITING, Provider 100 | #1001 ACCEPTED, Provider 101\n";
    cout << "Example booking number enter karo (0 = Back): ";
    cin >> number;
    if (number == 0) return;

    cout << "\n--- CANCELLATION FLOW: EXAMPLE BOOKING #" << number << " ---\n";
    cout << "- Sirf WAITING ya ACCEPTED booking cancel ho sakti hai.\n";
    cout << "- WAITING ho: Provider ki waiting queue se target Booking* remove hota hai.\n";
    cout << "- ACCEPTED ho: Provider main queue aur accepted-view queue se target remove hota hai.\n";
    cout << "- User active stack se Booking* remove karne ke liye temp stack use hota hai; baaki order preserve hota hai.\n";
    cout << "- Status CANCELLED hota hai; same pointer User cancelled/rejected-history stack par PUSH hota hai.\n";
    cout << "- COMPLETED booking cancel nahi kar sakte. Invalid/not-active booking par cancellation nahi hogi.\n";
    cout << "Example result: Booking #" << number << " -> status CANCELLED -> User cancellation history mein latest item.\n";
    cout << "History stack full ho to oldest history item drop hoti hai, taaki latest 5 rahein.\n";
    cout << "Note: status/list sach mein change nahi hui; ye explanation example hai.\n";
}

void show_active_bookings()
{
    cout << "\n--- RECENT ACTIVE BOOKINGS: EXAMPLE OUTPUT ---\n";
    cout << "TOP -> #1002 WAITING (Electrician)\n       -> #1001 ACCEPTED (Plumber)\n       -> #1000 WAITING (Carpenter)\n";
    cout << "Stack LIFO hai; newest booking TOP par hoti hai.\n";
    cout << "WAITING aur ACCEPTED bookings active stack mein rehti hain. Cancel/reject/complete hone par remove hoti hain.\n";
    cout << "Capacity 5; active stack full ho to new booking rok denge, old active booking auto-delete nahi hoti.\n";
}

void show_cancelled_bookings()
{
    cout << "\n--- CANCELLED / REJECTED HISTORY: EXAMPLE OUTPUT ---\n";
    cout << "TOP -> #1004 REJECTED (Provider ne reject ki)\n       -> #1003 CANCELLED (User ne cancel ki)\n       -> #0999 REJECTED\n";
    cout << "User cancellation ka status CANCELLED; Provider rejection ka status REJECTED hota hai.\n";
    cout << "Dono same history stack mein ja sakte hain, lekin status alag rehta hai.\n";
    cout << "LIFO: latest entry TOP par. Capacity 5; full ho to oldest history entry drop hoti hai.\n";
}

void show_completed_bookings()
{
    cout << "\n--- COMPLETED BOOKINGS: EXAMPLE OUTPUT ---\n";
    cout << "TOP -> #1005 COMPLETED - Electrician - Not rated yet\n       -> #1002 COMPLETED - Plumber - Not rated yet\n";
    cout << "Provider job complete mark karta hai to same Booking* User ke completed stack mein PUSH hota hai.\n";
    cout << "Latest completed booking TOP par hoti hai; rating ke liye yahin se booking select hoti hai.\n";
    cout << "Rated booking ko stack se remove kar sakte hain, taaki same booking dobara rate na ho. Capacity 5 hai.\n";
}

void rate_booking()
{
    int number, rating;
    cout << "\n--- GIVE RATING / REVIEW ---\n";
    cout << "Example unrated completed booking: #1005 | Provider ID 100 | Ramesh Kumar\n";
    cout << "Booking number enter karo (0 = Back): ";
    cin >> number;
    if (number == 0) return;
    cout << "Rating enter karo (1 se 5): ";
    cin >> rating;
    if (rating < 1 || rating > 5)
    {
        cout << "Invalid rating. Rating 1 se 5 ke beech honi chahiye.\n";
        return;
    }

    cout << "\n--- RATING UPDATE: EXAMPLE ---\n";
    cout << "Selected booking #" << number << " ko rating " << rating << "/5 di gayi.\n";
    cout << "Before: total_rating = 46, total_ratings_received = 10, average = 46/10 = 4.60\n";
    cout << "After : total_rating = " << 46 + rating << ", total_ratings_received = 11\n";
    cout << "Average = (46 + " << rating << ") / 11. Work count se divide nahi karna.\n";
    cout << "Rated Booking* completed stack se remove hota hai, taaki repeated rating na ho.\n";
    cout << "Actual project mein ye totals selected Provider object par update honge; is demo mein nahi.\n";
}

void user_booking_menu()
{
    int choice;
    while (1)
    {
        cout << "\n========== USER BOOKING MENU ==========\n";
        cout << "1. Create booking\n";
        cout << "2. Cancel booking\n";
        cout << "3. Recent active bookings\n";
        cout << "4. Recent cancelled/rejected bookings\n";
        cout << "5. Recent completed bookings\n";
        cout << "6. Rate a booking\n";
        cout << "0. Back\nChoice: ";
        cin >> choice;
        switch (choice)
        {
            case 1: create_booking(); break;
            case 2: cancel_booking(); break;
            case 3: show_active_bookings(); break;
            case 4: show_cancelled_bookings(); break;
            case 5: show_completed_bookings(); break;
            case 6: rate_booking(); break;
            case 0: return;
            default: cout << "Invalid choice.\n";
        }
    }
}

void user_dashboard()
{
    int choice;
    while (1)
    {
        cout << "\n========== USER DASHBOARD ==========\n";
        cout << "1. Display info\n";
        cout << "2. Change info\n";
        cout << "3. Booking menu\n";
        cout << "0. Sign out\nChoice: ";
        cin >> choice;
        switch (choice)
        {
            case 1: display_user_info(); break;
            case 2: change_user_info(); break;
            case 3: user_booking_menu(); break;
            case 0: cout << "User sign out. Main menu par wapas.\n"; return;
            default: cout << "Invalid choice.\n";
        }
    }
}

void process_booking()
{
    int choice;
    cout << "\n--- PROCESS FIRST WAITING REQUEST ---\n";
    cout << "Example waiting queue (FRONT -> REAR): #1002 WAITING, #1003 WAITING, #1004 WAITING\n";
    cout << "1. Accept\n2. Reject\n3. Keep waiting\n0. Back\nChoice: ";
    cin >> choice;
    switch (choice)
    {
        case 1:
            cout << "\nACCEPT EXAMPLE:\n";
            cout << "Before: Waiting FRONT #1002 -> #1003; Main queue: #1000 ACCEPTED\n";
            cout << "Main queue mein space check hota hai. Space hai to #1002 waiting queue se DEQUEUE hota hai.\n";
            cout << "Status WAITING -> ACCEPTED; same Booking* main circular queue ke REAR par ENQUEUE hota hai.\n";
            cout << "After : Waiting FRONT #1003; Main queue: #1000 -> #1002\n";
            cout << "Agar main queue full ho, request waiting queue mein hi rehti hai.\n";
            break;
        case 2:
            cout << "\nREJECT EXAMPLE:\n";
            cout << "#1002 waiting queue ke FRONT se DEQUEUE hoti hai; status REJECTED hota hai.\n";
            cout << "User ke active stack se #1002 remove; same pointer cancelled/rejected-history stack par PUSH.\n";
            cout << "Example result: User history TOP -> #1002 REJECTED.\n";
            break;
        case 3:
            cout << "\nKEEP WAITING EXAMPLE:\n";
            cout << "Before: FRONT #1002 -> #1003 -> #1004 REAR\n";
            cout << "#1002 ko FRONT se DEQUEUE karke same pointer REAR par ENQUEUE karte hain.\n";
            cout << "After : FRONT #1003 -> #1004 -> #1002 REAR; status WAITING hi rehta hai.\n";
            cout << "Isse doosri requests ko pehle process hone ka chance milta hai.\n";
            break;
        case 0: return;
        default: cout << "Invalid choice.\n";
    }
    cout << "Note: ye example queue state hai; demo mein actual queue/status update nahi hua.\n";
}

void show_accepted_bookings()
{
    cout << "\n--- ACCEPTED BOOKINGS / MAIN QUEUE: EXAMPLE OUTPUT ---\n";
    cout << "FRONT -> #1000 ACCEPTED (Plumber) -> #1002 ACCEPTED (Electrician) <- REAR\n";
    cout << "Main circular queue accepted bookings rakhti hai jab tak complete ya cancel na ho. Capacity = 5.\n";
    cout << "Circular index wrap ke liye (index + 1) % max use hota hai.\n";
}

void show_waiting_requests()
{
    cout << "\n--- WAITING REQUESTS: EXAMPLE OUTPUT ---\n";
    cout << "FRONT -> #1003 WAITING (Carpenter) -> #1004 WAITING (AC Repair) <- REAR\n";
    cout << "New booking REAR par enqueue hoti hai; provider FRONT se process karta hai (FIFO). Capacity = 5.\n";
    cout << "Waiting queue full hone par provider search results mein show nahi hota.\n";
}

void complete_booking()
{
    int number;
    cout << "\n--- MARK ACCEPTED BOOKING COMPLETE ---\n";
    cout << "Example accepted booking: #1002 | Provider ID 100 | User ID 1 | Status ACCEPTED\n";
    cout << "Booking number enter karo (0 = Back): ";
    cin >> number;
    if (number == 0) return;

    cout << "\n--- COMPLETION FLOW: EXAMPLE #" << number << " ---\n";
    cout << "1. Selected booking accepted-view queue aur Provider main queue se remove hoti hai.\n";
    cout << "2. Status ACCEPTED -> COMPLETED; Provider work_count +1 hota hai.\n";
    cout << "3. Same Booking* Provider recent-completed stack par PUSH hota hai.\n";
    cout << "4. User active stack se remove; User completed-booking stack par same pointer PUSH hota hai.\n";
    cout << "Example result: Provider completed TOP -> #" << number << " COMPLETED; User completed TOP -> #" << number << " COMPLETED.\n";
    cout << "Temp queue/stack use karke target remove hota hai aur baaki entries ka order preserve hota hai.\n";
    cout << "Note: sample state only; demo mein actual booking update nahi hui.\n";
}

void show_recent_completed_provider()
{
    cout << "\n--- PROVIDER RECENT COMPLETED BOOKINGS: EXAMPLE OUTPUT ---\n";
    cout << "TOP -> #1005 COMPLETED - Electrician - User Aditi Sharma\n";
    cout << "     -> #1002 COMPLETED - Plumber - User Rahul Verma\n";
    cout << "Stack LIFO hai; latest completed job TOP par hoti hai. Provider work_count job complete hote waqt +1 hota hai.\n";
}

void provider_request_menu()
{
    int choice;
    while (1)
    {
        cout << "\n========== PROVIDER REQUEST MENU ==========\n";
        cout << "1. Process first waiting request\n";
        cout << "2. View accepted bookings\n";
        cout << "3. View all waiting requests\n";
        cout << "4. Mark accepted booking complete\n";
        cout << "5. Recent completed bookings\n";
        cout << "0. Back\nChoice: ";
        cin >> choice;
        switch (choice)
        {
            case 1: process_booking(); break;
            case 2: show_accepted_bookings(); break;
            case 3: show_waiting_requests(); break;
            case 4: complete_booking(); break;
            case 5: show_recent_completed_provider(); break;
            case 0: return;
            default: cout << "Invalid choice.\n";
        }
    }
}

void provider_dashboard()
{
    int choice;
    while (1)
    {
        cout << "\n========== PROVIDER DASHBOARD ==========\n";
        cout << "1. Display info\n";
        cout << "2. Change info\n";
        cout << "3. Booking requests\n";
        cout << "0. Sign out\nChoice: ";
        cin >> choice;
        switch (choice)
        {
            case 1: display_provider_info(); break;
            case 2: change_provider_info(); break;
            case 3: provider_request_menu(); break;
            case 0: cout << "Provider sign out. Main menu par wapas.\n"; return;
            default: cout << "Invalid choice.\n";
        }
    }
}

void data_structure_working()
{
    cout << "\n[Quick Data-Structure Working - Shared by all 4 members]\n";
    int choice;
    while (1)
    {
        cout << "\n========== QUICK DATA-STRUCTURE WORKING ==========\n";
        cout << "1. Linked List + current_access pointer\n";
        cout << "2. Shared Booking pointer + User stacks\n";
        cout << "3. Provider circular queues\n";
        cout << "4. Temporary Stack/Queue\n";
        cout << "5. Search array + sorting\n";
        cout << "0. Back\nChoice: ";
        cin >> choice;
        switch (choice)
        {
            case 1:
                cout << "\nUser aur Provider linked lists mein signup par nodes END par attach hote hain.\n";
                cout << "Signup par object ka next pointer set hota hai aur node list ke END mein attach hota hai.\n";
                cout << "Sign-in list traverse karke ID/phone/email match karta hai. current_access_user/provider matched object ka address rakhta hai.\n";
                cout << "Example: current_access_user -> User ID 1, Aditi Sharma.\n";
                break;
            case 2:
                cout << "\nEk Booking object ka pointer User ke alag booking-history stacks mein store hota hai.\n";
                cout << "Ek Booking object ek hi baar banta hai. Usi Booking* ko User active stack aur Provider queue mein store kiya jata hai.\n";
                cout << "Example: Booking #1002 ka pointer User stack aur Provider waiting queue dono mein hai.\n";
                cout << "User ke Active, Cancelled/Rejected aur Completed stacks alag hain; har ek ki capacity 5 aur behavior LIFO hai.\n";
                cout << "Active full ho to new booking block; history full ho to oldest history entry drop ho sakti hai.\n";
                break;
            case 3:
                cout << "\nProvider waiting aur main circular queues booking status ke hisaab se use hoti hain.\n";
                cout << "Waiting queue: new WAITING request REAR par ENQUEUE, process FRONT se DEQUEUE (FIFO).\n";
                cout << "Accept hone par same pointer waiting se main circular queue mein move hota hai.\n";
                cout << "Example: Waiting #1002 -> accepted; waiting queue se nikal kar main queue mein aa gaya.\n";
                cout << "Circular queue next index = (index + 1) % max; max = 5.\n";
                break;
            case 4:
                cout << "\nTemporary stack/queue target booking remove karte waqt baaki entries ka order preserve karte hain.\n";
                cout << "Stack/queue ke beech se target item directly remove nahi hota. Baaki pointers temporary structure mein transfer hote hain.\n";
                cout << "Target pointer skip karke remaining pointers wapas transfer karte hain; relative order preserve hota hai.\n";
                cout << "Example: Queue [A, B, C] se B remove -> temp mein A,C -> original [A,C].\n";
                break;
            case 5:
                cout << "\nEk Booking object ka pointer User ke alag booking-history stacks mein store hota hai.\n";
                cout << "First linked-list pass matches count karti hai; exact-size Provider** array allocate hota hai; second pass usse fill karti hai.\n";
                cout << "Filter: service + area + waiting queue capacity. Rating/work_count descending sort ho sakti hai.\n";
                cout << "Example: results [Provider 100 rating 4.6, Provider 101 rating 4.3] -> rating sort mein 100 pehle.\n";
                cout << "Array use hone ke baad delete[] hota hai.\n";
                break;
            case 0: return;
            default: cout << "Invalid choice.\n";
        }
    }
}

int main()
{
    int choice;
    while (1)
    {
        cout << "\n========== LOCAL SERVICE BOOKING SYSTEM ==========\n";
        cout << "1. Sign up as User\n";
        cout << "2. Sign up as Provider\n";
        cout << "3. Sign in as User\n";
        cout << "4. Sign in as Provider\n";
        cout << "5. Quick data-structure working [Shared demonstration]\n";
        cout << "0. Exit\nChoice: ";
        cin >> choice;
        switch (choice)
        {
            case 1: sign_up_user(); break;
            case 2: sign_up_provider(); break;
            case 3:
                sign_in_explanation(1);
                user_dashboard();
                break;
            case 4:
                sign_in_explanation(0);
                provider_dashboard();
                break;
            case 5: data_structure_working(); break;
            case 0:
                cout << "Demo band. Ye sample program hai; real account ya booking save nahi hoti.\n";
                return 0;
            default: cout << "Invalid choice.\n";
        }
    }
}
