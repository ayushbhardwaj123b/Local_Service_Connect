```
#include <iostream>
#include <string>
using namespace std;

#define max 5

int next_user_id = 1;
int next_provider_id = 100;
int next_booking_number = 1000;

class User;
class Provider;

// Every booking is created once. Stacks and queues store its address.
class Booking
{
public:
    int booking_number;
    User* user_reference;
    Provider* provider_reference;
    string service;
    string area;
    string status;

    Booking(int number, User* user, Provider* provider, string service_name, string area_name)
    {
        booking_number = number;
        user_reference = user;
        provider_reference = provider;
        service = service_name;
        area = area_name;
        status = "WAITING";
    }
};

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

// Linked lists: User and Provider objects themselves are the nodes.
User* user_linked_list_head = nullptr;
User* user_linked_list_tail = nullptr;
Provider* provider_linked_list_head = nullptr;
Provider* provider_linked_list_tail = nullptr;

User* current_access_user = nullptr;
Provider* current_access_provider = nullptr;

// pop() and dequeue() are void functions. This pointer carries the removed Booking
// to the next operation, keeping the data-structure functions simple.
Booking* data_structure_value = nullptr;

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

// ------------------------- USER CLASS: STACK FUNCTIONS -------------------------
void User::push_user_booking_stack(Booking* value)
{
    if (user_booking_stack_top == max - 1)
        cout << "User booking stack is full.\n";
    else
    {
        user_booking_stack_top++;
        user_booking_stack[user_booking_stack_top] = value;
    }
}

void User::pop_user_booking_stack()
{
    if (user_booking_stack_top == -1)
    {
        data_structure_value = nullptr;
        return;
    }

    data_structure_value = user_booking_stack[user_booking_stack_top];
    user_booking_stack_top--;
}

void User::push_temp_booking_stack(Booking* value)
{
    if (temp_booking_stack_top < max - 1)
    {
        temp_booking_stack_top++;
        temp_booking_stack[temp_booking_stack_top] = value;
    }
}

void User::pop_temp_booking_stack()
{
    if (temp_booking_stack_top == -1)
    {
        data_structure_value = nullptr;
        return;
    }

    data_structure_value = temp_booking_stack[temp_booking_stack_top];
    temp_booking_stack_top--;
}

void User::remove_user_booking_from_stack(Booking* target)
{
    temp_booking_stack_top = -1;

    while (user_booking_stack_top != -1)
    {
        pop_user_booking_stack();
        if (data_structure_value != target)
            push_temp_booking_stack(data_structure_value);
    }

    while (temp_booking_stack_top != -1)
    {
        pop_temp_booking_stack();
        push_user_booking_stack(data_structure_value);
    }
}

void User::push_temp_cancel_booking_stack(Booking* value)
{
    if (temp_cancel_booking_stack_top < max - 1)
    {
        temp_cancel_booking_stack_top++;
        temp_cancel_booking_stack[temp_cancel_booking_stack_top] = value;
    }
}

void User::pop_temp_cancel_booking_stack()
{
    if (temp_cancel_booking_stack_top == -1)
    {
        data_structure_value = nullptr;
        return;
    }

    data_structure_value = temp_cancel_booking_stack[temp_cancel_booking_stack_top];
    temp_cancel_booking_stack_top--;
}

void User::pop_cancel_booking_stack()
{
    if (cancel_booking_stack_top == -1)
    {
        data_structure_value = nullptr;
        return;
    }

    data_structure_value = cancel_booking_stack[cancel_booking_stack_top];
    cancel_booking_stack_top--;
}

void User::push_cancel_booking_stack(Booking* value)
{
    // If full, drop the oldest booking and preserve the newest four.
    if (cancel_booking_stack_top == max - 1)
    {
        temp_cancel_booking_stack_top = -1;
        while (cancel_booking_stack_top > 0)
        {
            pop_cancel_booking_stack();
            push_temp_cancel_booking_stack(data_structure_value);
        }

        cancel_booking_stack_top = -1;
        while (temp_cancel_booking_stack_top != -1)
        {
            pop_temp_cancel_booking_stack();
            push_cancel_booking_stack(data_structure_value);
        }
    }

    cancel_booking_stack_top++;
    cancel_booking_stack[cancel_booking_stack_top] = value;
}

void User::push_temp_completed_booking_stack(Booking* value)
{
    if (temp_completed_booking_stack_top < max - 1)
    {
        temp_completed_booking_stack_top++;
        temp_completed_booking_stack[temp_completed_booking_stack_top] = value;
    }
}

void User::pop_temp_completed_booking_stack()
{
    if (temp_completed_booking_stack_top == -1)
    {
        data_structure_value = nullptr;
        return;
    }

    data_structure_value = temp_completed_booking_stack[temp_completed_booking_stack_top];
    temp_completed_booking_stack_top--;
}

void User::pop_completed_booking_stack()
{
    if (completed_booking_stack_top == -1)
    {
        data_structure_value = nullptr;
        return;
    }

    data_structure_value = completed_booking_stack[completed_booking_stack_top];
    completed_booking_stack_top--;
}

void User::push_completed_booking_stack(Booking* value)
{
    if (completed_booking_stack_top == max - 1)
    {
        temp_completed_booking_stack_top = -1;
        while (completed_booking_stack_top > 0)
        {
            pop_completed_booking_stack();
            push_temp_completed_booking_stack(data_structure_value);
        }

        completed_booking_stack_top = -1;
        while (temp_completed_booking_stack_top != -1)
        {
            pop_temp_completed_booking_stack();
            push_completed_booking_stack(data_structure_value);
        }
    }

    completed_booking_stack_top++;
    completed_booking_stack[completed_booking_stack_top] = value;
}

void User::remove_user_completed_booking_stack(Booking* target)
{
    temp_completed_booking_stack_top = -1;

    while (completed_booking_stack_top != -1)
    {
        pop_completed_booking_stack();
        if (data_structure_value != target)
            push_temp_completed_booking_stack(data_structure_value);
    }

    while (temp_completed_booking_stack_top != -1)
    {
        pop_temp_completed_booking_stack();
        push_completed_booking_stack(data_structure_value);
    }
}

void User::display_user_booking_stack()
{
    if (user_booking_stack_top == -1)
    {
        cout << "No active bookings.\n";
        return;
    }

    cout << "\n--- ACTIVE BOOKINGS (latest first) ---\n";
    int i;
    for (i = user_booking_stack_top; i >= 0; i--)
    {
        Booking* value = user_booking_stack[i];
        cout << "Booking: " << value->booking_number << " | " << value->service
             << " | " << value->area << " | Status: " << value->status << "\n";
    }
}

void User::display_cancel_booking_stack()
{
    if (cancel_booking_stack_top == -1)
    {
        cout << "No cancelled/rejected bookings.\n";
        return;
    }

    cout << "\n--- RECENT CANCELLED / REJECTED BOOKINGS ---\n";
    int i;
    for (i = cancel_booking_stack_top; i >= 0; i--)
    {
        Booking* value = cancel_booking_stack[i];
        cout << "Booking: " << value->booking_number << " | " << value->service
             << " | Status: " << value->status << "\n";
    }
}

void User::display_completed_booking_stack()
{
    if (completed_booking_stack_top == -1)
    {
        cout << "No completed bookings waiting for rating.\n";
        return;
    }

    cout << "\n--- COMPLETED BOOKINGS WAITING FOR RATING ---\n";
    int i;
    for (i = completed_booking_stack_top; i >= 0; i--)
    {
        Booking* value = completed_booking_stack[i];
        cout << "Booking: " << value->booking_number << " | " << value->service
             << " | Provider: " << value->provider_reference->name << "\n";
    }
}

// ------------------------- PROVIDER CLASS: QUEUE FUNCTIONS -------------------------
void Provider::enqueue_provider_waiting_queue(Booking* value)
{
    if (provider_waiting_queue_front == (provider_waiting_queue_rear + 1) % max)
        cout << "Provider waiting queue is full.\n";
    else if (provider_waiting_queue_front == -1 && provider_waiting_queue_rear == -1)
    {
        provider_waiting_queue_front = 0;
        provider_waiting_queue_rear = 0;
        provider_waiting_queue[0] = value;
    }
    else
    {
        provider_waiting_queue_rear = (provider_waiting_queue_rear + 1) % max;
        provider_waiting_queue[provider_waiting_queue_rear] = value;
    }
}

void Provider::dequeue_provider_waiting_queue()
{
    if (provider_waiting_queue_front == -1 && provider_waiting_queue_rear == -1)
    {
        data_structure_value = nullptr;
        return;
    }

    data_structure_value = provider_waiting_queue[provider_waiting_queue_front];
    if (provider_waiting_queue_front == provider_waiting_queue_rear)
        provider_waiting_queue_front = provider_waiting_queue_rear = -1;
    else
        provider_waiting_queue_front = (provider_waiting_queue_front + 1) % max;
}

void Provider::enqueue_temp_waiting_queue(Booking* value)
{
    if (temp_waiting_queue_front == (temp_waiting_queue_rear + 1) % max)
        cout << "Temporary waiting queue is full.\n";
    else if (temp_waiting_queue_front == -1 && temp_waiting_queue_rear == -1)
    {
        temp_waiting_queue_front = 0;
        temp_waiting_queue_rear = 0;
        temp_waiting_queue[0] = value;
    }
    else
    {
        temp_waiting_queue_rear = (temp_waiting_queue_rear + 1) % max;
        temp_waiting_queue[temp_waiting_queue_rear] = value;
    }
}

void Provider::dequeue_temp_waiting_queue()
{
    if (temp_waiting_queue_front == -1 && temp_waiting_queue_rear == -1)
    {
        data_structure_value = nullptr;
        return;
    }

    data_structure_value = temp_waiting_queue[temp_waiting_queue_front];
    if (temp_waiting_queue_front == temp_waiting_queue_rear)
        temp_waiting_queue_front = temp_waiting_queue_rear = -1;
    else
        temp_waiting_queue_front = (temp_waiting_queue_front + 1) % max;
}

void Provider::remove_from_provider_waiting_queue(Booking* target)
{
    temp_waiting_queue_front = temp_waiting_queue_rear = -1;

    while (provider_waiting_queue_front != -1)
    {
        dequeue_provider_waiting_queue();
        if (data_structure_value != target)
            enqueue_temp_waiting_queue(data_structure_value);
    }

    while (temp_waiting_queue_front != -1)
    {
        dequeue_temp_waiting_queue();
        enqueue_provider_waiting_queue(data_structure_value);
    }
}

void Provider::display_provider_waiting_queue()
{
    if (provider_waiting_queue_front == -1)
    {
        cout << "Waiting queue has no requests.\n";
        return;
    }

    cout << "\n--- WAITING REQUESTS (front first) ---\n";
    int i = provider_waiting_queue_front;
    while (1)
    {
        Booking* value = provider_waiting_queue[i];
        cout << "Booking: " << value->booking_number << " | User: " << value->user_reference->name
             << " | Phone: " << value->user_reference->phone << " | Service: " << value->service
             << " | Status: " << value->status << "\n";
        if (i == provider_waiting_queue_rear)
            break;
        i = (i + 1) % max;
    }
}

void Provider::enqueue_provider_main_queue(Booking* value)
{
    if (provider_main_queue_front == (provider_main_queue_rear + 1) % max)
        cout << "Provider main queue is full.\n";
    else if (provider_main_queue_front == -1 && provider_main_queue_rear == -1)
    {
        provider_main_queue_front = provider_main_queue_rear = 0;
        provider_main_queue[0] = value;
    }
    else
    {
        provider_main_queue_rear = (provider_main_queue_rear + 1) % max;
        provider_main_queue[provider_main_queue_rear] = value;
    }
}

void Provider::dequeue_provider_main_queue()
{
    if (provider_main_queue_front == -1 && provider_main_queue_rear == -1)
    {
        data_structure_value = nullptr;
        return;
    }

    data_structure_value = provider_main_queue[provider_main_queue_front];
    if (provider_main_queue_front == provider_main_queue_rear)
        provider_main_queue_front = provider_main_queue_rear = -1;
    else
        provider_main_queue_front = (provider_main_queue_front + 1) % max;
}

void Provider::enqueue_temp_main_queue(Booking* value)
{
    if (temp_main_queue_front == (temp_main_queue_rear + 1) % max)
        cout << "Temporary main queue is full.\n";
    else if (temp_main_queue_front == -1 && temp_main_queue_rear == -1)
    {
        temp_main_queue_front = temp_main_queue_rear = 0;
        temp_main_queue[0] = value;
    }
    else
    {
        temp_main_queue_rear = (temp_main_queue_rear + 1) % max;
        temp_main_queue[temp_main_queue_rear] = value;
    }
}

void Provider::dequeue_temp_main_queue()
{
    if (temp_main_queue_front == -1 && temp_main_queue_rear == -1)
    {
        data_structure_value = nullptr;
        return;
    }

    data_structure_value = temp_main_queue[temp_main_queue_front];
    if (temp_main_queue_front == temp_main_queue_rear)
        temp_main_queue_front = temp_main_queue_rear = -1;
    else
        temp_main_queue_front = (temp_main_queue_front + 1) % max;
}

void Provider::remove_from_provider_main_queue(Booking* target)
{
    temp_main_queue_front = temp_main_queue_rear = -1;

    while (provider_main_queue_front != -1)
    {
        dequeue_provider_main_queue();
        if (data_structure_value != target)
            enqueue_temp_main_queue(data_structure_value);
    }

    while (temp_main_queue_front != -1)
    {
        dequeue_temp_main_queue();
        enqueue_provider_main_queue(data_structure_value);
    }
}

void Provider::display_provider_main_queue()
{
    if (provider_main_queue_front == -1)
    {
        cout << "Main queue has no accepted bookings.\n";
        return;
    }

    cout << "\n--- ACCEPTED BOOKINGS (front first) ---\n";
    int i = provider_main_queue_front;
    while (1)
    {
        Booking* value = provider_main_queue[i];
        cout << "Booking: " << value->booking_number << " | User: " << value->user_reference->name
             << " | Phone: " << value->user_reference->phone << " | Service: " << value->service
             << " | Status: " << value->status << "\n";
        if (i == provider_main_queue_rear)
            break;
        i = (i + 1) % max;
    }
}

void Provider::enqueue_accepted_booking_queue(Booking* value)
{
    if (accepted_booking_queue_front == (accepted_booking_queue_rear + 1) % max)
        cout << "Accepted booking queue is full.\n";
    else if (accepted_booking_queue_front == -1 && accepted_booking_queue_rear == -1)
    {
        accepted_booking_queue_front = accepted_booking_queue_rear = 0;
        accepted_booking_queue[0] = value;
    }
    else
    {
        accepted_booking_queue_rear = (accepted_booking_queue_rear + 1) % max;
        accepted_booking_queue[accepted_booking_queue_rear] = value;
    }
}

void Provider::dequeue_accepted_booking_queue()
{
    if (accepted_booking_queue_front == -1 && accepted_booking_queue_rear == -1)
    {
        data_structure_value = nullptr;
        return;
    }

    data_structure_value = accepted_booking_queue[accepted_booking_queue_front];
    if (accepted_booking_queue_front == accepted_booking_queue_rear)
        accepted_booking_queue_front = accepted_booking_queue_rear = -1;
    else
        accepted_booking_queue_front = (accepted_booking_queue_front + 1) % max;
}

void Provider::enqueue_temp_accepted_booking_queue(Booking* value)
{
    if (temp_accepted_booking_queue_front == (temp_accepted_booking_queue_rear + 1) % max)
        cout << "Temporary accepted queue is full.\n";
    else if (temp_accepted_booking_queue_front == -1 && temp_accepted_booking_queue_rear == -1)
    {
        temp_accepted_booking_queue_front = temp_accepted_booking_queue_rear = 0;
        temp_accepted_booking_queue[0] = value;
    }
    else
    {
        temp_accepted_booking_queue_rear = (temp_accepted_booking_queue_rear + 1) % max;
        temp_accepted_booking_queue[temp_accepted_booking_queue_rear] = value;
    }
}

void Provider::dequeue_temp_accepted_booking_queue()
{
    if (temp_accepted_booking_queue_front == -1 && temp_accepted_booking_queue_rear == -1)
    {
        data_structure_value = nullptr;
        return;
    }

    data_structure_value = temp_accepted_booking_queue[temp_accepted_booking_queue_front];
    if (temp_accepted_booking_queue_front == temp_accepted_booking_queue_rear)
        temp_accepted_booking_queue_front = temp_accepted_booking_queue_rear = -1;
    else
        temp_accepted_booking_queue_front = (temp_accepted_booking_queue_front + 1) % max;
}

void Provider::prepare_accepted_booking_queue()
{
    accepted_booking_queue_front = accepted_booking_queue_rear = -1;

    if (provider_main_queue_front == -1)
        return;

    int i = provider_main_queue_front;
    while (1)
    {
        Booking* value = provider_main_queue[i];
        if (value->status == "ACCEPTED")
            enqueue_accepted_booking_queue(value);
        if (i == provider_main_queue_rear)
            break;
        i = (i + 1) % max;
    }
}

void Provider::remove_from_accepted_booking_queue(Booking* target)
{
    temp_accepted_booking_queue_front = temp_accepted_booking_queue_rear = -1;

    while (accepted_booking_queue_front != -1)
    {
        dequeue_accepted_booking_queue();
        if (data_structure_value != target)
            enqueue_temp_accepted_booking_queue(data_structure_value);
    }

    while (temp_accepted_booking_queue_front != -1)
    {
        dequeue_temp_accepted_booking_queue();
        enqueue_accepted_booking_queue(data_structure_value);
    }
}

void Provider::display_accepted_booking_queue()
{
    if (accepted_booking_queue_front == -1)
    {
        cout << "No accepted booking is available to complete.\n";
        return;
    }

    cout << "\n--- ACCEPTED BOOKINGS TO COMPLETE ---\n";
    int i = accepted_booking_queue_front;
    while (1)
    {
        Booking* value = accepted_booking_queue[i];
        cout << "Booking: " << value->booking_number << " | User: " << value->user_reference->name
             << " | Service: " << value->service << " | Status: " << value->status << "\n";
        if (i == accepted_booking_queue_rear)
            break;
        i = (i + 1) % max;
    }
}

// ------------------------- SEARCH / SORT / CREATE BOOKING -------------------------
void create_booking()
{
    if (current_access_user->user_booking_stack_top == max - 1)
    {
        cout << "Your active booking stack is full (maximum 5).\n";
        return;
    }

    string service, area;
    int choice;

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
            cout << "Invalid service choice. Booking cancelled.\n";
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
            cout << "Invalid area choice. Booking cancelled.\n";
            return;
    }

    // Pass 1: count exact matches. A provider is shown only if waiting queue is not full.
    int count = 0;
    Provider* temp = provider_linked_list_head;
    while (temp != nullptr)
    {
        if (temp->service == service && temp->area == area &&
            temp->provider_waiting_queue_front != (temp->provider_waiting_queue_rear + 1) % max)
            count++;
        temp = temp->provider_next;
    }

    if (count == 0)
    {
        cout << "No available provider found for this service and area.\n";
        return;
    }

    // Pass 2: dynamically allocate only the number of matching Provider pointers.
    Provider** results = new Provider*[count];
    temp = provider_linked_list_head;
    int index = 0;
    while (temp != nullptr)
    {
        if (temp->service == service && temp->area == area &&
            temp->provider_waiting_queue_front != (temp->provider_waiting_queue_rear + 1) % max)
        {
            results[index] = temp;
            index++;
        }
        temp = temp->provider_next;
    }

    cout << "\nDisplay providers by:\n1. Current order\n2. Highest rating\n3. Highest completed work\n";
    cout << "Enter choice: ";
    cin >> choice;
    cin.ignore();

    int i, j;
    if (choice == 2)
    {
        for (i = 0; i < count - 1; i++)
        {
            for (j = 0; j < count - i - 1; j++)
            {
                double first_rating = 0, second_rating = 0;
                if (results[j]->total_ratings_received > 0)
                    first_rating = results[j]->total_rating / results[j]->total_ratings_received;
                if (results[j + 1]->total_ratings_received > 0)
                    second_rating = results[j + 1]->total_rating / results[j + 1]->total_ratings_received;

                if (first_rating < second_rating)
                {
                    Provider* swap_provider = results[j];
                    results[j] = results[j + 1];
                    results[j + 1] = swap_provider;
                }
            }
        }
    }
    else if (choice == 3)
    {
        for (i = 0; i < count - 1; i++)
        {
            for (j = 0; j < count - i - 1; j++)
            {
                if (results[j]->work_count < results[j + 1]->work_count)
                {
                    Provider* swap_provider = results[j];
                    results[j] = results[j + 1];
                    results[j + 1] = swap_provider;
                }
            }
        }
    }
    else if (choice != 1)
    {
        cout << "Invalid choice. Current order will be used.\n";
    }

    cout << "\n--- AVAILABLE PROVIDERS ---\n";
    for (i = 0; i < count; i++)
    {
        double average_rating = 0;
        if (results[i]->total_ratings_received > 0)
            average_rating = results[i]->total_rating / results[i]->total_ratings_received;

        cout << i + 1 << ". " << results[i]->name << " | ID: " << results[i]->id
             << " | Service: " << results[i]->service << " | Area: " << results[i]->area
             << " | Rating: " << average_rating << "/5"
             << " | Completed work: " << results[i]->work_count << "\n";
    }

    cout << "0. Cancel\nChoose provider: ";
    cin >> choice;
    cin.ignore();
    if (choice == 0)
    {
        delete[] results;
        return;
    }
    if (choice < 1 || choice > count)
    {
        cout << "Invalid provider choice.\n";
        delete[] results;
        return;
    }

    Provider* selected_provider = results[choice - 1];
    delete[] results;

    // Check again before creating a booking.
    if (selected_provider->provider_waiting_queue_front ==
        (selected_provider->provider_waiting_queue_rear + 1) % max)
    {
        cout << "This provider's waiting queue is full.\n";
        return;
    }

    Booking* new_booking = new Booking(next_booking_number, current_access_user,
                                       selected_provider, service, area);
    next_booking_number++;
    selected_provider->enqueue_provider_waiting_queue(new_booking);
    current_access_user->push_user_booking_stack(new_booking);

    cout << "Booking created successfully. Booking number: " << new_booking->booking_number
         << " | Initial status: WAITING\n";
}

// ------------------------- CANCEL BOOKING -------------------------
void cancel_booking()
{
    current_access_user->display_user_booking_stack();
    if (current_access_user->user_booking_stack_top == -1)
        return;

    int number;
    cout << "Enter booking number to cancel (0 to go back): ";
    cin >> number;
    cin.ignore();
    if (number == 0)
        return;

    Booking* target = nullptr;
    int i;
    for (i = current_access_user->user_booking_stack_top; i >= 0; i--)
    {
        if (current_access_user->user_booking_stack[i]->booking_number == number)
            target = current_access_user->user_booking_stack[i];
    }

    if (target == nullptr)
    {
        cout << "That booking is not in your active booking stack.\n";
        return;
    }

    if (target->status != "WAITING" && target->status != "ACCEPTED")
    {
        cout << "This booking cannot be cancelled in its current status.\n";
        return;
    }

    if (target->status == "WAITING")
        target->provider_reference->remove_from_provider_waiting_queue(target);
    else
    {
        target->provider_reference->remove_from_provider_main_queue(target);
        target->provider_reference->remove_from_accepted_booking_queue(target);
    }

    current_access_user->remove_user_booking_from_stack(target);
    target->status = "CANCELLED";
    current_access_user->push_cancel_booking_stack(target);
    cout << "Booking cancelled and moved to cancelled history.\n";
}

// ------------------------- RATE BOOKING -------------------------
void rate_booking()
{
    current_access_user->display_completed_booking_stack();
    if (current_access_user->completed_booking_stack_top == -1)
        return;

    int number;
    cout << "Enter completed booking number to rate (0 to go back): ";
    cin >> number;
    cin.ignore();
    if (number == 0)
        return;

    Booking* target = nullptr;
    int i;
    for (i = current_access_user->completed_booking_stack_top; i >= 0; i--)
    {
        if (current_access_user->completed_booking_stack[i]->booking_number == number)
            target = current_access_user->completed_booking_stack[i];
    }

    if (target == nullptr)
    {
        cout << "Booking not found in your completed booking stack.\n";
        return;
    }

    int rating;
    cout << "Give rating from 1 to 5: ";
    cin >> rating;
    cin.ignore();
    if (rating < 1 || rating > 5)
    {
        cout << "Rating must be between 1 and 5.\n";
        return;
    }

    target->provider_reference->total_rating += rating;
    target->provider_reference->total_ratings_received++;

    double average_rating = target->provider_reference->total_rating /
                            target->provider_reference->total_ratings_received;
    cout << "Rating saved. Provider's average rating is now " << average_rating << "/5.\n";

    // Remove rated booking so it cannot be rated twice.
    current_access_user->remove_user_completed_booking_stack(target);
}

// ------------------------- USER BOOKING MENU -------------------------
void user_booking_menu()
{
    int choice;
    while (1)
    {
        cout << "\n--- USER BOOKING MENU ---\n";
        cout << "1. Create booking\n2. Cancel booking\n3. Recent active bookings\n";
        cout << "4. Recent cancelled/rejected bookings\n5. Recent completed bookings\n";
        cout << "6. Rate a booking\n0. Back\nEnter choice: ";
        cin >> choice;
        cin.ignore();

        switch (choice)
        {
            case 1: create_booking(); break;
            case 2: cancel_booking(); break;
            case 3: current_access_user->display_user_booking_stack(); break;
            case 4: current_access_user->display_cancel_booking_stack(); break;
            case 5: current_access_user->display_completed_booking_stack(); break;
            case 6: rate_booking(); break;
            case 0: return;
            default: cout << "Invalid choice.\n";
        }
    }
}

// ------------------------- PROVIDER CLASS: RECENT COMPLETED STACK -------------------------
void Provider::push_temp_recent_completed_booking_stack(Booking* value)
{
    if (temp_recent_completed_booking_stack_top < max - 1)
    {
        temp_recent_completed_booking_stack_top++;
        temp_recent_completed_booking_stack[temp_recent_completed_booking_stack_top] = value;
    }
}

void Provider::pop_temp_recent_completed_booking_stack()
{
    if (temp_recent_completed_booking_stack_top == -1)
    {
        data_structure_value = nullptr;
        return;
    }

    data_structure_value = temp_recent_completed_booking_stack[temp_recent_completed_booking_stack_top];
    temp_recent_completed_booking_stack_top--;
}

void Provider::pop_recent_completed_booking_stack()
{
    if (recent_completed_booking_stack_top == -1)
    {
        data_structure_value = nullptr;
        return;
    }

    data_structure_value = recent_completed_booking_stack[recent_completed_booking_stack_top];
    recent_completed_booking_stack_top--;
}

void Provider::push_recent_completed_booking_stack(Booking* value)
{
    if (recent_completed_booking_stack_top == max - 1)
    {
        temp_recent_completed_booking_stack_top = -1;
        while (recent_completed_booking_stack_top > 0)
        {
            pop_recent_completed_booking_stack();
            push_temp_recent_completed_booking_stack(data_structure_value);
        }

        recent_completed_booking_stack_top = -1;
        while (temp_recent_completed_booking_stack_top != -1)
        {
            pop_temp_recent_completed_booking_stack();
            recent_completed_booking_stack_top++;
            recent_completed_booking_stack[recent_completed_booking_stack_top] = data_structure_value;
        }
    }

    recent_completed_booking_stack_top++;
    recent_completed_booking_stack[recent_completed_booking_stack_top] = value;
}

void Provider::display_recent_completed_booking_stack()
{
    if (recent_completed_booking_stack_top == -1)
    {
        cout << "No completed bookings yet.\n";
        return;
    }

    cout << "\n--- RECENT COMPLETED BOOKINGS ---\n";
    int i;
    for (i = recent_completed_booking_stack_top; i >= 0; i--)
    {
        Booking* value = recent_completed_booking_stack[i];
        cout << "Booking: " << value->booking_number << " | User: " << value->user_reference->name
             << " | Service: " << value->service << "\n";
    }
}

// ------------------------- PROCESS PROVIDER REQUEST -------------------------
void process_booking()
{
    if (current_access_provider->provider_waiting_queue_front == -1)
    {
        cout << "No waiting requests to process.\n";
        return;
    }

    Booking* first_booking = current_access_provider->provider_waiting_queue[
        current_access_provider->provider_waiting_queue_front];
    cout << "\n--- FIRST WAITING REQUEST ---\n";
    cout << "Booking number: " << first_booking->booking_number << "\n";
    cout << "User: " << first_booking->user_reference->name << "\n";
    cout << "Phone: " << first_booking->user_reference->phone << "\n";
    cout << "Email: " << first_booking->user_reference->email << "\n";
    cout << "Service: " << first_booking->service << "\nArea: " << first_booking->area << "\n";
    cout << "Status: " << first_booking->status << "\n";

    int choice;
    cout << "1. Accept\n2. Reject\n3. Keep waiting\n0. Back\nEnter choice: ";
    cin >> choice;
    cin.ignore();
    if (choice == 0)
        return;

    if (choice == 1)
    {
        if (current_access_provider->provider_main_queue_front ==
            (current_access_provider->provider_main_queue_rear + 1) % max)
        {
            cout << "Main queue is full. Cannot accept this booking right now.\n";
            return;
        }

        current_access_provider->dequeue_provider_waiting_queue();
        Booking* value = data_structure_value;
        value->status = "ACCEPTED";
        current_access_provider->enqueue_provider_main_queue(value);
        cout << "Booking accepted and moved to the main queue.\n";
    }
    else if (choice == 2)
    {
        current_access_provider->dequeue_provider_waiting_queue();
        Booking* value = data_structure_value;
        value->status = "REJECTED";

        value->user_reference->remove_user_booking_from_stack(value);
        value->user_reference->push_cancel_booking_stack(value);
        cout << "Booking rejected and moved to user's cancelled/rejected history.\n";
    }
    else if (choice == 3)
    {
        // Keep status WAITING; move the front request to the back.
        current_access_provider->dequeue_provider_waiting_queue();
        Booking* value = data_structure_value;
        current_access_provider->enqueue_provider_waiting_queue(value);
        cout << "Booking remains waiting and has moved to the back.\n";
    }
    else
        cout << "Invalid choice.\n";
}

// ------------------------- COMPLETE BOOKING -------------------------
void complete_booking()
{
    current_access_provider->display_provider_main_queue();
    if (current_access_provider->provider_main_queue_front == -1)
        return;

    current_access_provider->prepare_accepted_booking_queue();
    current_access_provider->display_accepted_booking_queue();
    if (current_access_provider->accepted_booking_queue_front == -1)
        return;

    int number;
    cout << "Enter accepted booking number to mark complete (0 to go back): ";
    cin >> number;
    cin.ignore();
    if (number == 0)
        return;

    Booking* target = nullptr;
    int i = current_access_provider->accepted_booking_queue_front;
    while (1)
    {
        if (current_access_provider->accepted_booking_queue[i]->booking_number == number)
            target = current_access_provider->accepted_booking_queue[i];
        if (i == current_access_provider->accepted_booking_queue_rear)
            break;
        i = (i + 1) % max;
    }

    if (target == nullptr)
    {
        cout << "Accepted booking not found.\n";
        return;
    }

    current_access_provider->remove_from_accepted_booking_queue(target);
    current_access_provider->remove_from_provider_main_queue(target);
    target->status = "COMPLETED";
    current_access_provider->work_count++;
    current_access_provider->push_recent_completed_booking_stack(target);

    target->user_reference->remove_user_booking_from_stack(target);
    target->user_reference->push_completed_booking_stack(target);

    cout << "Booking marked COMPLETED. Work count updated.\n";
}

void provider_request_menu()
{
    int choice;
    while (1)
    {
        cout << "\n--- PROVIDER REQUEST MENU ---\n";
        cout << "1. Process first waiting request\n2. View all accepted bookings (main queue)\n";
        cout << "3. View all waiting requests\n4. Mark accepted booking complete\n";
        cout << "5. Recent completed bookings\n0. Back\nEnter choice: ";
        cin >> choice;
        cin.ignore();

        switch (choice)
        {
            case 1: process_booking(); break;
            case 2: current_access_provider->display_provider_main_queue(); break;
            case 3: current_access_provider->display_provider_waiting_queue(); break;
            case 4: complete_booking(); break;
            case 5: current_access_provider->display_recent_completed_booking_stack(); break;
            case 0: return;
            default: cout << "Invalid choice.\n";
        }
    }
}

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

// ------------------------- MAIN MENU -------------------------
int main()
{
    while (1)
    {
        int choice;
        cout << "\n========== LOCAL SERVICE BOOKING SYSTEM ==========\n";
        cout << "1. Sign up as User\n2. Sign up as Provider\n";
        cout << "3. Sign in as User\n4. Sign in as Provider\n0. Exit\nEnter choice: ";
        cin >> choice;
        cin.ignore();

        switch (choice)
        {
            case 1:
                sign_up_user();
                break;
            case 2:
                sign_up_provider();
                break;
            case 3:
                sign_in_user();
                if (current_access_user != nullptr)
                    user_dashboard();
                break;
            case 4:
                sign_in_provider();
                if (current_access_provider != nullptr)
                    provider_dashboard();
                break;
            case 0:
                cout << "Thank you for using Local Service Booking System.\n";
                return 0;
            default:
                cout << "Invalid choice.\n";
        }
    }
}


```