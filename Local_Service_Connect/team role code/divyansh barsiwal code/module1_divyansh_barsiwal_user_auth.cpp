// =====================================================================
// LOCAL SERVICE BOOKING SYSTEM - MODULE 1
// Member      : Divyansh Barsiwal
// Role        : User + Authentication
// Contribution: User signup, sign-in, password recovery, user details/profile change, user dashboard; owns the User class and the user linked list
// Depends on : Module 3 (user_booking_menu is opened from user_dashboard); main() in Module 3 file calls its signup/sign-in/dashboard
//
// Is file mein sirf is member ka code hai (original single-file code se
// as-it-is nikala gaya, koi logic change nahi). Har block ke upar
// original file ke line numbers likhe hain.
// Poora program chalane ke liye original single .cpp use hota hai.
// =====================================================================

// ---------- Global counter: next_user_id  (original lines 8-8) ----------
int next_user_id = 1;

// ---------- class User (profile + user stacks declaration)  (original lines 37-110) ----------
class User
{
public:
    int id;
    string name;
    string phone;
    string email;
    string password;
    string area;
    string best_friend_name;
    string personal_email_answer;
    User* user_next;

    // Each User object has its own separate stacks. Capacity of each is 5.
    Booking* user_booking_stack[max];
    int user_booking_stack_top;

    Booking* cancel_booking_stack[max];
    int cancel_booking_stack_top;

    Booking* completed_booking_stack[max];
    int completed_booking_stack_top;

    // Temporary stacks belong to this User too, so different Users never share them.
    Booking* temp_booking_stack[max];
    int temp_booking_stack_top;
    Booking* temp_cancel_booking_stack[max];
    int temp_cancel_booking_stack_top;
    Booking* temp_completed_booking_stack[max];
    int temp_completed_booking_stack_top;

    void push_user_booking_stack(Booking* value);
    void pop_user_booking_stack();
    void push_temp_booking_stack(Booking* value);
    void pop_temp_booking_stack();
    void remove_user_booking_from_stack(Booking* target);

    void push_cancel_booking_stack(Booking* value);
    void pop_cancel_booking_stack();
    void push_temp_cancel_booking_stack(Booking* value);
    void pop_temp_cancel_booking_stack();

    void push_completed_booking_stack(Booking* value);
    void pop_completed_booking_stack();
    void push_temp_completed_booking_stack(Booking* value);
    void pop_temp_completed_booking_stack();
    void remove_user_completed_booking_stack(Booking* target);

    void display_user_booking_stack();
    void display_cancel_booking_stack();
    void display_completed_booking_stack();

    User(string user_name, string user_phone, string user_email, string user_password,
         string user_area, string friend_name, string email_answer)
    {
        id = next_user_id;
        next_user_id++;
        name = user_name;
        phone = user_phone;
        email = user_email;
        password = user_password;
        area = user_area;
        best_friend_name = friend_name;
        personal_email_answer = email_answer;
        user_next = nullptr;

        user_booking_stack_top = -1;
        cancel_booking_stack_top = -1;
        completed_booking_stack_top = -1;
        temp_booking_stack_top = -1;
        temp_cancel_booking_stack_top = -1;
        temp_completed_booking_stack_top = -1;
    }
};

// ---------- Global: user linked-list head/tail  (original lines 222-224) ----------
// Linked lists: User and Provider objects themselves are the nodes.
User* user_linked_list_head = nullptr;
User* user_linked_list_tail = nullptr;

// ---------- Global: current_access_user  (original lines 228-228) ----------
User* current_access_user = nullptr;

// ---------- insert_user_at_end() - linked list  (original lines 235-248) ----------
// ------------------------- LINKED LISTS -------------------------
void insert_user_at_end(User* new_user)
{
    if (user_linked_list_head == nullptr)
    {
        user_linked_list_head = new_user;
        user_linked_list_tail = new_user;
    }
    else
    {
        user_linked_list_tail->user_next = new_user;
        user_linked_list_tail = new_user;
    }
}

// ---------- sign_up_user()  (original lines 264-304) ----------
// ------------------------- SIGN UP -------------------------
void sign_up_user()
{
    string name, phone, email, password, area, friend_name, email_answer;
    int choice;

    cout << "\n--- USER SIGN UP ---\n";
    cout << "Name: ";
    getline(cin, name);
    cout << "Phone: ";
    getline(cin, phone);
    cout << "Email: ";
    getline(cin, email);
    cout << "Password: ";
    getline(cin, password);

    cout << "\nChoose your area:\n1. Rishikesh\n2. Raipur\n3. Dehradun\n4. Clement Town\n5. Prem Nagar\n";
    cout << "Enter choice: ";
    cin >> choice;
    cin.ignore();
    switch (choice)
    {
        case 1: area = "Rishikesh"; break;
        case 2: area = "Raipur"; break;
        case 3: area = "Dehradun"; break;
        case 4: area = "Clement Town"; break;
        case 5: area = "Prem Nagar"; break;
        default:
            cout << "Invalid area choice. Signup cancelled.\n";
            return;
    }

    cout << "Security question - best friend's name: ";
    getline(cin, friend_name);
    cout << "Security question - personal email answer: ";
    getline(cin, email_answer);

    User* new_user = new User(name, phone, email, password, area, friend_name, email_answer);
    insert_user_at_end(new_user);
    cout << "Signup successful. Your User ID is: " << new_user->id << "\n";
}

// ---------- forgot_user_password()  (original lines 368-386) ----------
// ------------------------- PASSWORD RECOVERY -------------------------
void forgot_user_password()
{
    string friend_name, email_answer;
    cout << "Best friend's name: ";
    getline(cin, friend_name);
    cout << "Personal email security answer: ";
    getline(cin, email_answer);

    if (friend_name == current_access_user->best_friend_name &&
        email_answer == current_access_user->personal_email_answer)
    {
        cout << "Enter new password: ";
        getline(cin, current_access_user->password);
        cout << "Password changed successfully.\n";
    }
    else
        cout << "Security answers do not match.\n";
}

// ---------- sign_in_user()  (original lines 407-453) ----------
// ------------------------- SIGN IN -------------------------
void sign_in_user()
{
    string info, password;
    User* temp = user_linked_list_head;
    current_access_user = nullptr;

    cout << "\n--- USER SIGN IN ---\n";
    cout << "Enter User ID, phone, or email: ";
    getline(cin, info);

    while (temp != nullptr)
    {
        if (info == to_string(temp->id) || info == temp->phone || info == temp->email)
        {
            current_access_user = temp;
            break;
        }
        temp = temp->user_next;
    }

    if (current_access_user == nullptr)
    {
        cout << "User ID, phone, or email not found.\n";
        return;
    }

    cout << "Password: ";
    getline(cin, password);
    if (password == current_access_user->password)
    {
        cout << "Welcome, " << current_access_user->name << "!\n";
        return;
    }

    int choice;
    cout << "Incorrect password.\n1. Forgot password\n0. Back\nEnter choice: ";
    cin >> choice;
    cin.ignore();
    if (choice == 1)
    {
        forgot_user_password();
        if (current_access_user->password != "")
            cout << "You can try signing in again from the main menu.\n";
    }
    current_access_user = nullptr;
}

// ---------- display_user_info() + change_user_info()  (original lines 501-590) ----------
// ------------------------- DISPLAY / CHANGE USER INFO -------------------------
void display_user_info()
{
    cout << "\n--- USER INFORMATION ---\n";
    cout << "ID: " << current_access_user->id << "\n";
    cout << "Name: " << current_access_user->name << "\n";
    cout << "Phone: " << current_access_user->phone << "\n";
    cout << "Email: " << current_access_user->email << "\n";
    cout << "Area: " << current_access_user->area << "\n";
}

void change_user_info()
{
    int choice;
    string value, previous_value;
    cout << "\n1. Change name\n2. Change phone\n3. Change email\n4. Change area\n";
    cout << "5. Change password\n6. Change security answers\n0. Back\nEnter choice: ";
    cin >> choice;
    cin.ignore();

    switch (choice)
    {
        case 1:
            cout << "Enter new name: ";
            getline(cin, current_access_user->name);
            break;
        case 2:
            cout << "Enter new phone: ";
            getline(cin, current_access_user->phone);
            break;
        case 3:
            cout << "Enter previous email: ";
            getline(cin, previous_value);
            if (previous_value == current_access_user->email)
            {
                cout << "Enter new email: ";
                getline(cin, current_access_user->email);
            }
            else
                cout << "Previous email is incorrect.\n";
            break;
        case 4:
            cout << "Choose area:\n1. Rishikesh\n2. Raipur\n3. Dehradun\n4. Clement Town\n5. Prem Nagar\n";
            cout << "Enter choice: ";
            cin >> choice;
            cin.ignore();
            switch (choice)
            {
                case 1: current_access_user->area = "Rishikesh"; break;
                case 2: current_access_user->area = "Raipur"; break;
                case 3: current_access_user->area = "Dehradun"; break;
                case 4: current_access_user->area = "Clement Town"; break;
                case 5: current_access_user->area = "Prem Nagar"; break;
                default: cout << "Invalid area choice.\n";
            }
            break;
        case 5:
            cout << "Enter previous password: ";
            getline(cin, previous_value);
            if (previous_value == current_access_user->password)
            {
                cout << "Enter new password: ";
                getline(cin, current_access_user->password);
                cout << "Password changed.\n";
            }
            else
                cout << "Previous password is incorrect.\n";
            break;
        case 6:
            cout << "Verify best friend's name: ";
            getline(cin, previous_value);
            cout << "Verify personal email security answer: ";
            getline(cin, value);
            if (previous_value == current_access_user->best_friend_name &&
                value == current_access_user->personal_email_answer)
            {
                cout << "Enter new best friend's name: ";
                getline(cin, current_access_user->best_friend_name);
                cout << "Enter new personal email security answer: ";
                getline(cin, current_access_user->personal_email_answer);
            }
            else
                cout << "Security answers are incorrect.\n";
            break;
        case 0:
            break;
        default:
            cout << "Invalid choice.\n";
    }
}

// ---------- user_dashboard()  (original lines 1798-1818) ----------
// ------------------------- DASHBOARDS -------------------------
void user_dashboard()
{
    int choice;
    while (1)
    {
        cout << "\n--- USER DASHBOARD ---\n";
        cout << "1. Display info\n2. Change info\n3. Booking menu\n0. Sign out\nEnter choice: ";
        cin >> choice;
        cin.ignore();

        switch (choice)
        {
            case 1: display_user_info(); break;
            case 2: change_user_info(); break;
            case 3: user_booking_menu(); break;
            case 0: current_access_user = nullptr; return;
            default: cout << "Invalid choice.\n";
        }
    }
}
