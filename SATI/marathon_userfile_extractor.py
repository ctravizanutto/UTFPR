import pandas as pd

'''
usernumber=0
usersitenumber=1
userfullname=Null
userdesc=[NULL] *name*
userpassword=*email up to @*
username=*email*
userenabled=t
'''
def user_pattern(index: int, name: str, email: str) -> str:
    index = index + 1 # must start at 1
    return f"usernumber={index}\n" \
    "usersitenumber=1\n" \
    f"userfullname={name}\n" \
    f"userdesc={name.split()[0]}\n" \
    f"userpassword={email.split('@')[0]}\n" \
    f"username={email}\n" \
    "userenabled=t\n\n"

if __name__ == '__main__':
    marathon_list = pd.read_excel('activity_registrants.xlsx')
    with open('usuarios.txt', 'w') as users:
        for index, row in marathon_list.iterrows():
            name = row['Nome']
            email = row['Email']

            users.write(user_pattern(index, name, email))
