# Local Service Booking System: Team Contribution

A terminal-based C++ simulation where users find local service providers (plumber, electrician, etc.) by service and area, book them, and rate them after the job. Every menu option runs a real data-structure operation behind it (linked lists, stacks, circular queues, sorting, dynamic memory).

The project code was written as one `.cpp` file. For this report it has been split into four files, one per member. Code is copied as-is, with no logic changes. Each block in a file is labelled with its original line numbers.

| Member | Module | File | Code lines |
|---|---|---|---|
| Divyansh Barsiwal | 1: User + Authentication | `module1_divyansh_barsiwal_user_auth.cpp` | 288 (17%) |
| Rakshita Pant | 2: Provider + Profile | `module2_rakshita_pant_provider_profile.cpp` | 361 (22%) |
| Devyansh Bhardwaj | 3: Search + User Booking, plus overall coordination | `module3_devyansh_bhardwaj_search_booking.cpp` | 319 (19%) |
| Ashutosh Negi | 4: Requests + Completion (Overall Project Leader) | `module4_ashutosh_negi_requests_completion.cpp` | 706 (42%) |

Total: 1674 lines of code, all assigned, none counted twice.

---

## Module 1: Divyansh Barsiwal (User + Authentication)

**What he built**
- `User` class: profile fields (ID, name, phone, email, password, area, security answers) and the user's own booking stacks.
- User linked list: new users are added at the end (`insert_user_at_end`).
- `sign_up_user()`: collects details, creates the User object, assigns the ID (starts from 1).
- `sign_in_user()`: finds the user by ID, phone or email in the linked list, then checks the password.
- `forgot_user_password()`: resets the password using the two security answers.
- `display_user_info()` and `change_user_info()`: view and edit profile (with previous-value verification for email, password and security answers).
- `user_dashboard()`: the menu shown after login.

**Builds on / connects to**
- His dashboard opens `user_booking_menu()` from Module 3.
- `current_access_user` (set at sign-in) is the pointer that Modules 3 and 4 use to know who is logged in.

---

## Module 2: Rakshita Pant (Provider + Profile)

**What she built**
- `Provider` class: profile fields plus service, area, rating total, rating count, work count, and the provider's own queues and stack.
- Provider linked list: new providers are added at the end (`insert_provider_at_end`).
- `sign_up_provider()`: collects details, then service and area from menus; the provider ID starts from 100.
- `sign_in_provider()` and `forgot_provider_password()`: same login and recovery flow as the user side.
- `display_provider_info()` (shows average rating and completed work) and `change_provider_info()` (adds the service change option).
- `provider_dashboard()`: the menu shown after provider login.

**Builds on / connects to**
- Her provider linked list is the list that Module 3's search goes through.
- The rating and work count she displays are updated by Module 4 (rating and completion).
- Her dashboard opens `provider_request_menu()` from Module 4.

---

## Module 3: Devyansh Bhardwaj (Search + User Booking, plus overall coordination)

**What he built**
- `Booking` class: one booking object (number starting from 1000, user and provider references, service, area, status). The same object is shared by all stacks and queues through its pointer.
- `create_booking()`:
  - Pass 1 counts matching providers (service + area, waiting queue not full).
  - Pass 2 allocates an exact-size `Provider*` array with `new` and fills it.
  - Bubble sort by current order, highest average rating, or most completed work.
  - The user picks a provider and the Booking is created, then pushed to the user's active stack and enqueued in the provider's waiting queue.
  - The array is freed with `delete[]`.
- User active-booking stack (max 5): push, pop, temp stack, and removal of one booking from the middle.
- `display_user_booking_stack()` and `user_booking_menu()` (create, cancel, view active, cancelled and completed bookings, rate).
- Overall coordination: shared headers, the `max` size macro, forward declarations, and `main()` (the main menu that joins all modules).

**Builds on / connects to**
- Reads the provider linked list from Module 2 and uses `current_access_user` from Module 1.
- Calls Module 4's queue function to place the booking in the provider's waiting queue.
- Menu options for cancel, rate and history call Module 4's functions.
- `main()` calls the sign-up, sign-in and dashboard functions of Modules 1 and 2.

---

## Module 4: Ashutosh Negi (Requests + Completion, Overall Project Leader)

**What he built**
- Provider circular queues (max 5 each): waiting queue, main queue and accepted-booking view queue, each with enqueue, dequeue, display and a temp queue for removing a booking from the middle while keeping order.
- `process_booking()`: provider handles the first waiting request (Accept, Reject, or Keep waiting).
- `complete_booking()`: marks an accepted booking as completed and increases the provider's work count.
- `provider_request_menu()`: the provider's request-handling menu.
- Provider's recent-completed stack (max 5).
- User cancelled/rejected stack and completed stack (push, pop, temp stack, removal), with the display functions.
- `cancel_booking()`: cancels a WAITING or ACCEPTED booking and keeps the remaining order.
- `rate_booking()`: rating from 1 to 5, updates the provider's average, and removes the rated booking so it cannot be rated twice.
- `data_structure_value`: the shared pointer that carries the removed booking out of pop and dequeue.

**Builds on / connects to**
- Works on the `Booking` objects created in Module 3 and the user active stack from Module 3.
- Uses the `User` and `Provider` classes from Modules 1 and 2, and `current_access_provider` from Module 2.
- Module 2's profile shows the rating and work count that he updates.

---

## How the modules connect

1. **Module 1** and **Module 2**: users and providers sign up and sign in.
2. **Module 3**: a user searches, sorts, picks a provider and a Booking is created (status WAITING).
3. **Module 4**: the provider accepts, rejects or keeps it waiting; later marks it completed; the user can cancel or rate it.
4. The completed work and the rating then show up in the provider profile (Module 2) and in the next search (Module 3).

Note: the four files are split for reporting and do not compile separately. The original single `.cpp` is the one that runs.

---

## Demo Program: Menu + Working Demonstration

File: `Local_Service_Booking_System_Menu_Demo_Hinglish_Examples.cpp`

**What it is.** A presentation-only version of the project. It has the same menus as the real program, but each option only prints a short explanation of what is happening behind that option, along with a small example output (for instance sample users, providers, booking numbers and queue states). It is made to explain the project in the viva or presentation, and it lets the audience move through every menu without needing to type real data.

**What it does not do.**
- Nothing is saved: no account, booking, rating or queue is actually created or changed. Every output is a sample, and the program says so at the end of each option.
- Sign-in does not check any ID or password. It prints how the real sign-in works and opens the dashboard directly.
- No real data structures run in it. It only describes how linked lists, stacks and circular queues would be used in the real program.

**What the user sees.** The main menu has the same options as the real program (sign up and sign in as User or Provider, Exit), plus option 5, *Quick data-structure working*, which is a shared explanation by all four members.

### Which menu option shows whose work

| Menu option in the demo | What it explains | Module / Member |
|---|---|---|
| Main menu 1: Sign up as User | New User object, ID starting from 1, node added at the end of the user linked list | Module 1: Divyansh Barsiwal |
| Main menu 3: Sign in as User | Linked-list search by ID/phone/email, password check, `current_access_user` pointer, password recovery | Module 1: Divyansh Barsiwal |
| User dashboard: Display info / Change info | Profile display and update on the same User object | Module 1: Divyansh Barsiwal |
| Main menu 2: Sign up as Provider | Provider object with service and area, ID starting from 100, added to the provider linked list | Module 2: Rakshita Pant |
| Main menu 4: Sign in as Provider | Same sign-in flow for Provider, `current_access_provider` pointer | Module 2: Rakshita Pant |
| Provider dashboard: Display info / Change info | Provider profile, average rating = total rating / ratings received | Module 2: Rakshita Pant |
| User booking menu: 1. Create booking | Service + area search, 2-pass search with a dynamic `Provider**` array, bubble sort, provider selection, Booking object creation | Module 3: Devyansh Bhardwaj |
| User booking menu: 3. Recent active bookings | User active-booking stack (LIFO, capacity 5) | Module 3: Devyansh Bhardwaj |
| User booking menu: 2. Cancel booking | Removal from the waiting/main queue and user stack using a temp structure, status CANCELLED | Module 4: Ashutosh Negi |
| User booking menu: 4. Cancelled/rejected, 5. Completed | User cancelled/rejected and completed stacks | Module 4: Ashutosh Negi |
| User booking menu: 6. Rate a booking | Rating 1 to 5, provider average update, rated booking removed from the stack | Module 4: Ashutosh Negi |
| Provider request menu: 1. Process first waiting request | Accept, Reject, or Keep waiting on the waiting circular queue (FIFO) | Module 4: Ashutosh Negi |
| Provider request menu: 2. Accepted bookings, 3. Waiting requests | Main queue and waiting queue display | Module 4: Ashutosh Negi |
| Provider request menu: 4. Mark complete, 5. Recent completed | Completion flow, work count +1, provider and user completed stacks | Module 4: Ashutosh Negi |
| Main menu 5: Quick data-structure working | Linked list, shared Booking pointer, circular queues, temp stack/queue, search array and sorting | Shared by all four members |

Note: the dashboards and menus (`user_dashboard`, `provider_dashboard`, `user_booking_menu`, `provider_request_menu`) call each other in the same way as the real program, so the demo also shows how the four modules connect.
