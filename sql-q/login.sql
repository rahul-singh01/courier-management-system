SELECT TRUE
FROM users
WHERE passwd_hash = "hash" AND email="email"
UNION
SELECT TRUE
FROM companies
WHERE passwd_hash = "hash" AND email="email";