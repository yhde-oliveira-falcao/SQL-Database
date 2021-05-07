-- Yuri Falcao
-- 112624192
-- Lab 3

-- Q1 Display the information of all offices.
select * from offices;

-- Q2 Display the employee number for all employees whose office code is 1. 
select * from employees where officeCode =1; 

-- Q3 Display customer number, customer name, contact first name and contact last name, and phone for all customers in Paris.
select customerNumber, customerName, contactFirstName, contactLastName, phone from customers where city = 'Paris'; 

-- Q4 Display customer number for customers who have payments.
select distinct customerNumber from payments;

-- Q5 List customer numbers, check number, and amount for customers whose payment amount is not in the 
--  range of $30,000 to $65,000. Sort the output by top payments amount first.
select customerNumber, checkNumber, amount from payments where amount not between 30000 and 6500 order by amount DESC;
-- CAN BE AMOUNT NOT BETWEEN 30000 AND 65000...

-- Q6 Display the order information for all orders that are cancelled. 
select * from orders where status = 'Cancelled'; 

-- Q7. Display the information of all products with string ‘co’ in their product name. (c and o can be lower or upper case).
select * from products where lower (productName) like '%co%';

-- Q8. Display all customers whose contact first name starts with letter s (both lowercase and uppercase) and includes letter 
-- e (both lowercase and uppercase).
select * from customers where lower (contactFirstName) like 's%e%';