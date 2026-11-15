// =====================================================================
// LOCAL SERVICE BOOKING SYSTEM - MODULE 2
// Member      : Rakshita Pant
// Role        : Provider + Profile
// Contribution: Provider signup (service + area), sign-in, password recovery, provider profile change, provider dashboard; owns the Provider class and the provider linked list
// Depends on : Module 4 (provider_request_menu is opened from provider_dashboard; rating/work_count shown in profile are updated by Module 4)
//
// Is file mein sirf is member ka code hai (original single-file code se
// as-it-is nikala gaya, koi logic change nahi). Har block ke upar
// original file ke line numbers likhe hain.
// Poora program chalane ke liye original single .cpp use hota hai.
// =====================================================================

// ---------- Global counter: next_provider_id  (original lines 9-9) ----------
int next_provider_id = 100;

// ---------- class Provider (profile + queues/stack declaration)  (original lines 112-220) ----------
class Provider
{
public:
    int id;
    string name;
    string phone;
    string email;
    string password;
    string service;
    string area;
    string best_friend_name;
    string personal_email_answer;
    double total_rating;
    int total_ratings_received;
    int work_count;
    Provider* provider_next;

    // Each Provider object has its own separate queues and stack. Capacity is 5.
    Booking* provider_waiting_queue[max];
    int provider_waiting_queue_front;
    int provider_waiting_queue_rear;

    Booking* provider_main_queue[max];
    int provider_main_queue_front;
    int provider_main_queue_rear;

    Booking* accepted_booking_queue[max];
    int accepted_booking_queue_front;
    int accepted_booking_queue_rear;

    Booking* recent_completed_booking_stack[max];
    int recent_completed_booking_stack_top;

    // Temporary structures belong to this Provider, not to every Provider collectively.
    Booking* temp_waiting_queue[max];
    int temp_waiting_queue_front;
    int temp_waiting_queue_rear;
    Booking* temp_main_queue[max];
    int temp_main_queue_front;
    int temp_main_queue_rear;
    Booking* temp_accepted_booking_queue[max];
    int temp_accepted_booking_queue_front;
    int temp_accepted_booking_queue_rear;
    Booking* temp_recent_completed_booking_stack[max];
    int temp_recent_completed_booking_stack_top;

    void enqueue_provider_waiting_queue(Booking* value);
    void dequeue_provider_waiting_queue();
    void enqueue_temp_waiting_queue(Booking* value);
    void dequeue_temp_waiting_queue();
    void remove_from_provider_waiting_queue(Booking* target);
    void display_provider_waiting_queue();

    void enqueue_provider_main_queue(Booking* value);
    void dequeue_provider_main_queue();
    void enqueue_temp_main_queue(Booking* value);
    void dequeue_temp_main_queue();
    void remove_from_provider_main_queue(Booking* target);
    void display_provider_main_queue();

    void enqueue_accepted_booking_queue(Booking* value);
    void dequeue_accepted_booking_queue();
    void enqueue_temp_accepted_booking_queue(Booking* value);
    void dequeue_temp_accepted_booking_queue();
    void prepare_accepted_booking_queue();
    void remove_from_accepted_booking_queue(Booking* target);
    void display_accepted_booking_queue();

    void push_temp_recent_completed_booking_stack(Booking* value);
    void pop_temp_recent_completed_booking_stack();
    void pop_recent_completed_booking_stack();
    void push_recent_completed_booking_stack(Booking* value);
    void display_recent_completed_booking_stack();

    Provider(string provider_name, string provider_phone, string provider_email,
             string provider_password, string provider_service, string provider_area,
             string friend_name, string email_answer)
    {
        id = next_provider_id;
        next_provider_id++;
        name = provider_name;
        phone = provider_phone;
        email = provider_email;
        password = provider_password;
        service = provider_service;
        area = provider_area;
        best_friend_name = friend_name;
        personal_email_answer = email_answer;
        total_rating = 0;
        total_ratings_received = 0;
        work_count = 0;
        provider_next = nullptr;

        provider_waiting_queue_front = -1;
        provider_waiting_queue_rear = -1;
        provider_main_queue_front = -1;
        provider_main_queue_rear = -1;
        accepted_booking_queue_front = -1;
        accepted_booking_queue_rear = -1;
        recent_completed_booking_stack_top = -1;
        temp_waiting_queue_front = -1;
        temp_waiting_queue_rear = -1;
        temp_main_queue_front = -1;
        temp_main_queue_rear = -1;
        temp_accepted_booking_queue_front = -1;
        temp_accepted_booking_queue_rear = -1;
        temp_recent_completed_booking_stack_top = -1;
    }
};

// ---------- Global: provider linked-list head/tail  (original lines 225-226) ----------
Provider* provider_linked_list_head = nullptr;
Provider* provider_linked_list_tail = nullptr;

// ---------- Global: current_access_provider  (original lines 229-229) ----------
Provider* current_access_provider = nullptr;

// ---------- insert_provider_at_end() - linked list  (original lines 250-262) ----------
void insert_provider_at_end(Provider* new_provider)
{
    if (provider_linked_list_head == nullptr)
    {
        provider_linked_list_head = new_provider;
        provider_linked_list_tail = new_provider;
    }
    else
    {
        provider_linked_list_tail->provider_next = new_provider;
        provider_linked_list_tail = new_provider;
    }
}

// ---------- sign_up_provider()  (original lines 306-366) ----------
void sign_up_provider()
{
    string name, phone, email, password, service, area, friend_name, email_answer;
    int choice;

    cout << "\n--- PROVIDER SIGN UP ---\n";
    cout << "Name: ";
    getline(cin, name);
    cout << "Phone: ";
    getline(cin, phone);
    cout << "Email: ";
    getline(cin, email);
    cout << "Password: ";
    getline(cin, password);

    cout << "\nChoose service:\n1. Plumber\n2. Carpenter\n3. Electrician\n4. Geyser Repair\n";
    cout << "5. AC Repair\n6. Painter\n7. Cleaner\n8. Appliance Repair\n9. Vegetable Vendor\n";
    cout << "Enter choice: ";
    cin >> choice;
    cin.ignore();
    switch (choice)
    {
        case 1: service = "Plumber"; break;
        case 2: service = "Carpenter"; break;
        case 3: service = "Electrician"; break;
        case 4: service = "Geyser Repair"; break;
        case 5: service = "AC Repair"; break;
        case 6: service = "Painter"; break;
        case 7: service = "Cleaner"; break;
        case 8: service = "Appliance Repair"; break;
        case 9: service = "Vegetable Vendor"; break;
        default:
            cout << "Invalid service choice. Signup cancelled.\n";
            return;
    }

    cout << "\nChoose area:\n1. Rishikesh\n2. Raipur\n3. Dehradun\n4. Clement Town\n5. Prem Nagar\n";
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

    Provider* new_provider = new Provider(name, phone, email, password, service, area, friend_name, email_answer);
    insert_provider_at_end(new_provider);
    cout << "Signup successful. Your Provider ID is: " << new_provider->id << "\n";
}

// ---------- forgot_provider_password()  (original lines 388-405) ----------
void forgot_provider_password()
{
    string friend_name, email_answer;
    cout << "Best friend's name: ";
    getline(cin, friend_name);
    cout << "Personal email security answer: ";
    getline(cin, email_answer);

    if (friend_name == current_access_provider->best_friend_name &&
        email_answer == current_access_provider->personal_email_answer)
    {
        cout << "Enter new password: ";
        getline(cin, current_access_provider->password);
        cout << "Password changed successfully.\n";
    }
    else
        cout << "Security answers do not match.\n";
}

// ---------- sign_in_provider()  (original lines 455-499) ----------
void sign_in_provider()
{
    string info, password;
    Provider* temp = provider_linked_list_head;
    current_access_provider = nullptr;

    cout << "\n--- PROVIDER SIGN IN ---\n";
    cout << "Enter Provider ID, phone, or email: ";
    getline(cin, info);

    while (temp != nullptr)
    {
        if (info == to_string(temp->id) || info == temp->phone || info == temp->email)
        {
            current_access_provider = temp;
            break;
        }
        temp = temp->provider_next;
    }

    if (current_access_provider == nullptr)
    {
        cout << "Provider ID, phone, or email not found.\n";
        return;
    }

    cout << "Password: ";
    getline(cin, password);
    if (password == current_access_provider->password)
    {
        cout << "Welcome, " << current_access_provider->name << "!\n";
        return;
    }

    int choice;
    cout << "Incorrect password.\n1. Forgot password\n0. Back\nEnter choice: ";
    cin >> choice;
    cin.ignore();
    if (choice == 1)
    {
        forgot_provider_password();
        cout << "You can try signing in again from the main menu.\n";
    }
    current_access_provider = nullptr;
}

// ---------- display_provider_info() + change_provider_info()  (original lines 592-708) ----------
// ------------------------- DISPLAY / CHANGE PROVIDER INFO -------------------------
void display_provider_info()
{
    double average_rating = 0;
    if (current_access_provider->total_ratings_received > 0)
        average_rating = current_access_provider->total_rating / current_access_provider->total_ratings_received;

    cout << "\n--- PROVIDER INFORMATION ---\n";
    cout << "ID: " << current_access_provider->id << "\n";
    cout << "Name: " << current_access_provider->name << "\n";
    cout << "Phone: " << current_access_provider->phone << "\n";
    cout << "Email: " << current_access_provider->email << "\n";
    cout << "Service: " << current_access_provider->service << "\n";
    cout << "Area: " << current_access_provider->area << "\n";
    cout << "Average rating: " << average_rating << " / 5\n";
    cout << "Completed work count: " << current_access_provider->work_count << "\n";
}

void change_provider_info()
{
    int choice;
    string value, previous_value;
    cout << "\n1. Change name\n2. Change phone\n3. Change email\n4. Change service\n";
    cout << "5. Change area\n6. Change password\n7. Change security answers\n0. Back\nEnter choice: ";
    cin >> choice;
    cin.ignore();

    switch (choice)
    {
        case 1:
            cout << "Enter new name: ";
            getline(cin, current_access_provider->name);
            break;
        case 2:
            cout << "Enter new phone: ";
            getline(cin, current_access_provider->phone);
            break;
        case 3:
            cout << "Enter previous email: ";
            getline(cin, previous_value);
            if (previous_value == current_access_provider->email)
            {
                cout << "Enter new email: ";
                getline(cin, current_access_provider->email);
            }
            else
                cout << "Previous email is incorrect.\n";
            break;
        case 4:
            cout << "Choose service:\n1. Plumber\n2. Carpenter\n3. Electrician\n4. Geyser Repair\n";
            cout << "5. AC Repair\n6. Painter\n7. Cleaner\n8. Appliance Repair\n9. Vegetable Vendor\n";
            cout << "Enter choice: ";
            cin >> choice;
            cin.ignore();
            switch (choice)
            {
                case 1: current_access_provider->service = "Plumber"; break;
                case 2: current_access_provider->service = "Carpenter"; break;
                case 3: current_access_provider->service = "Electrician"; break;
                case 4: current_access_provider->service = "Geyser Repair"; break;
                case 5: current_access_provider->service = "AC Repair"; break;
                case 6: current_access_provider->service = "Painter"; break;
                case 7: current_access_provider->service = "Cleaner"; break;
                case 8: current_access_provider->service = "Appliance Repair"; break;
                case 9: current_access_provider->service = "Vegetable Vendor"; break;
                default: cout << "Invalid service choice.\n";
            }
            break;
        case 5:
            cout << "Choose area:\n1. Rishikesh\n2. Raipur\n3. Dehradun\n4. Clement Town\n5. Prem Nagar\n";
            cout << "Enter choice: ";
            cin >> choice;
            cin.ignore();
            switch (choice)
            {
                case 1: current_access_provider->area = "Rishikesh"; break;
                case 2: current_access_provider->area = "Raipur"; break;
                case 3: current_access_provider->area = "Dehradun"; break;
                case 4: current_access_provider->area = "Clement Town"; break;
                case 5: current_access_provider->area = "Prem Nagar"; break;
                default: cout << "Invalid area choice.\n";
            }
            break;
        case 6:
            cout << "Enter previous password: ";
            getline(cin, previous_value);
            if (previous_value == current_access_provider->password)
            {
                cout << "Enter new password: ";
                getline(cin, current_access_provider->password);
                cout << "Password changed.\n";
            }
            else
                cout << "Previous password is incorrect.\n";
            break;
        case 7:
            cout << "Verify best friend's name: ";
            getline(cin, previous_value);
            cout << "Verify personal email security answer: ";
            getline(cin, value);
            if (previous_value == current_access_provider->best_friend_name &&
                value == current_access_provider->personal_email_answer)
            {
                cout << "Enter new best friend's name: ";
                getline(cin, current_access_provider->best_friend_name);
                cout << "Enter new personal email security answer: ";
                getline(cin, current_access_provider->personal_email_answer);
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

// ---------- provider_dashboard()  (original lines 1820-1839) ----------
void provider_dashboard()
{
    int choice;
    while (1)
    {
        cout << "\n--- PROVIDER DASHBOARD ---\n";
        cout << "1. Display info\n2. Change info\n3. Booking requests\n0. Sign out\nEnter choice: ";
        cin >> choice;
        cin.ignore();

        switch (choice)
        {
            case 1: display_provider_info(); break;
            case 2: change_provider_info(); break;
            case 3: provider_request_menu(); break;
            case 0: current_access_provider = nullptr; return;
            default: cout << "Invalid choice.\n";
        }
    }
}
