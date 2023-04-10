CREATE VIEW cour_from_to_name AS
SELECT 
    CONCAT(from_user.full_name, ' (', from_user.sn, ')') AS from_person_full_name,
    CONCAT(to_user.full_name, ' (', to_user.sn, ')') AS to_person_full_name
FROM 
    couriers 
    INNER JOIN user AS from_user ON couriers.from_person = from_user.sn
    INNER JOIN user AS to_user ON couriers.to_person = to_user.sn;
