// Simulated Database for Frontend Demo
const medicinesDatabase = [
    { name: 'Doliprane', dosage: '500mg', price: 120, pharmacy: 'Mauripharma', expiration: '2026-12-01', region: 'Nouakchott' },
    { name: 'Doliprane', dosage: '1000mg', price: 200, pharmacy: 'Central Pharmacy', expiration: '2025-10-10', region: 'Nouakchott' },
    { name: 'Paracetamol', dosage: '500mg', price: 100, pharmacy: 'Pharmacie Al Amal', expiration: '2027-01-01', region: 'Rosso' },
    { name: 'Ibuprofen', dosage: '200mg', price: 150, pharmacy: 'Pharma City', expiration: '2026-06-30', region: 'Nouakchott' },
    { name: 'Paracetamol', dosage: '1000mg', price: 180, pharmacy: 'Central Pharmacy', expiration: '2026-08-15', region: 'Nouakchott' },
    { name: 'Aspirin', dosage: '500mg', price: 90, pharmacy: 'Mauripharma', expiration: '2027-03-20', region: 'Nouakchott' },
];

const pharmaciesDatabase = [
    { name: 'Mauripharma', region: 'Nouakchott', isOpen: true, rating: 4.5 },
    { name: 'Central Pharmacy', region: 'Nouakchott', isOpen: true, rating: 4.8 },
    { name: 'Pharmacie Al Amal', region: 'Rosso', isOpen: false, rating: 4.2 },
    { name: 'Pharma City', region: 'Nouakchott', isOpen: true, rating: 4.6 },
];

const medicineEquivalents = {
    'doliprane': ['paracetamol', 'acetaminophen'],
    'paracetamol': ['doliprane', 'acetaminophen'],
    'ibuprofen': ['advil', 'brufen'],
    'aspirin': ['cardio-aspirin', 'aspirine'],
};

let selectedRating = 0;

// Search Medicine Function
function searchMedicine() {
    const searchTerm = document.getElementById('medicineSearch').value.toLowerCase().trim();
    const resultsContainer = document.getElementById('searchResults');
    
    if (!searchTerm) {
        resultsContainer.innerHTML = '<div class="empty-state"><p>Veuillez entrer un nom de médicament</p></div>';
        return;
    }

    const results = medicinesDatabase.filter(med => 
        med.name.toLowerCase().includes(searchTerm) ||
        med.dosage.toLowerCase().includes(searchTerm)
    );

    if (results.length === 0) {
        resultsContainer.innerHTML = '<div class="empty-state"><p>Aucun médicament trouvé. Essayez une autre recherche.</p></div>';
        return;
    }

    resultsContainer.innerHTML = results.map(med => `
        <div class="result-card">
            <div class="result-header">
                <div>
                    <div class="medicine-name">${med.name}</div>
                    <div class="dosage">${med.dosage}</div>
                </div>
                <div class="price">${med.price} UM</div>
            </div>
            <div class="pharmacy-info">
                <div class="pharmacy-name">💊 ${med.pharmacy}</div>
                <div class="expiration-date">📅 Expiration: ${formatDate(med.expiration)}</div>
                <div class="expiration-date">📍 Région: ${med.region}</div>
                ${isExpirationSoon(med.expiration) ? 
                    '<div class="expiration-warning">⚠️ Proche de la date d\'expiration!</div>' : 
                    '<div class="expiration-ok">✓ Délai d\'expiration acceptable</div>'}
            </div>
        </div>
    `).join('');
}

// Filter Pharmacies by Region
function filterPharmacies() {
    const selectedRegion = document.getElementById('wilayas').value;
    const pharmacyList = document.getElementById('pharmacyList');
    
    let filteredPharmacies = pharmaciesDatabase;
    
    if (selectedRegion) {
        filteredPharmacies = pharmaciesDatabase.filter(pharmacy => 
            pharmacy.region === selectedRegion
        );
    }

    if (filteredPharmacies.length === 0) {
        pharmacyList.innerHTML = '<div class="empty-state"><p>Aucune pharmacie trouvée dans cette région.</p></div>';
        return;
    }

    pharmacyList.innerHTML = filteredPharmacies.map(pharmacy => `
        <div class="pharmacy-card">
            <div class="pharmacy-header">
                <h3>${pharmacy.name}</h3>
                <div class="pharmacy-rating">${generateStars(pharmacy.rating)}</div>
            </div>
            <span class="pharmacy-status ${pharmacy.isOpen ? 'status-open' : 'status-closed'}">
                ${pharmacy.isOpen ? '🟢 Ouvert' : '🔴 Fermé'}
            </span>
            <div class="pharmacy-details">
                <p><strong>Région:</strong> ${pharmacy.region}</p>
                <p><strong>Évaluation:</strong> ${pharmacy.rating}/5</p>
            </div>
        </div>
    `).join('');
}

// Compare Prices Function
function comparePrices() {
    const medicineName = document.getElementById('compareInput').value.toLowerCase().trim();
    const comparisonResults = document.getElementById('comparisonResults');
    
    if (!medicineName) {
        comparisonResults.innerHTML = '<div class="empty-state"><p>Veuillez entrer un nom de médicament</p></div>';
        return;
    }

    const results = medicinesDatabase
        .filter(med => med.name.toLowerCase().includes(medicineName))
        .sort((a, b) => a.price - b.price);

    if (results.length === 0) {
        comparisonResults.innerHTML = '<div class="empty-state"><p>Aucun résultat pour la comparaison.</p></div>';
        return;
    }

    let tableHTML = `
        <table class="comparison-table">
            <thead>
                <tr>
                    <th>Médicament</th>
                    <th>Dosage</th>
                    <th>Pharmacie</th>
                    <th>Prix</th>
                    <th>Région</th>
                </tr>
            </thead>
            <tbody>
    `;

    const minPrice = Math.min(...results.map(r => r.price));
    const maxPrice = Math.max(...results.map(r => r.price));

    results.forEach(result => {
        const priceClass = result.price === minPrice ? 'price-low' : result.price === maxPrice ? 'price-high' : '';
        tableHTML += `
            <tr>
                <td>${result.name}</td>
                <td>${result.dosage}</td>
                <td>${result.pharmacy}</td>
                <td class="${priceClass}">${result.price} UM</td>
                <td>${result.region}</td>
            </tr>
        `;
    });

    tableHTML += `
            </tbody>
        </table>
    `;

    comparisonResults.innerHTML = tableHTML;
}

// Check Expiration Function
function checkExpirations() {
    const today = new Date();
    const thirtyDaysFromNow = new Date(today.getTime() + 30 * 24 * 60 * 60 * 1000);
    
    const expiringMeds = medicinesDatabase.filter(med => {
        const expDate = new Date(med.expiration);
        return expDate <= thirtyDaysFromNow && expDate >= today;
    });

    const expirationList = document.getElementById('expirationList');
    
    if (expiringMeds.length === 0) {
        expirationList.innerHTML = '<div class="empty-state"><p>✓ Aucun médicament n\'est proche de l\'expiration.</p></div>';
        return;
    }

    expirationList.innerHTML = expiringMeds.map(med => `
        <div class="result-card">
            <div class="result-header">
                <div>
                    <div class="medicine-name">⚠️ ${med.name}</div>
                    <div class="dosage">${med.dosage}</div>
                </div>
                <div class="price">${med.price} UM</div>
            </div>
            <div class="pharmacy-info">
                <div class="pharmacy-name">💊 ${med.pharmacy}</div>
                <div class="expiration-date">📅 Expiration: ${formatDate(med.expiration)}</div>
                <div class="expiration-warning">⚠️ Ce médicament expire bientôt!</div>
            </div>
        </div>
    `).join('');
}

// Show On Duty Pharmacies Function
function showOnDutyPharmacies() {
    const onDutyPharmacies = pharmaciesDatabase.filter(pharmacy => pharmacy.isOpen);
    const onDutyList = document.getElementById('onDutyList');
    
    if (onDutyPharmacies.length === 0) {
        onDutyList.innerHTML = '<div class="empty-state"><p>Aucune pharmacie ouverte actuellement.</p></div>';
        return;
    }

    onDutyList.innerHTML = onDutyPharmacies.map(pharmacy => `
        <div class="pharmacy-card">
            <div class="pharmacy-header">
                <h3>🟢 ${pharmacy.name}</h3>
                <div class="pharmacy-rating">${generateStars(pharmacy.rating)}</div>
            </div>
            <span class="pharmacy-status status-open">🟢 Ouvert maintenant</span>
            <div class="pharmacy-details">
                <p><strong>Région:</strong> ${pharmacy.region}</p>
                <p><strong>Évaluation:</strong> ${pharmacy.rating}/5</p>
                <p><strong>Horaires:</strong> 24h/24</p>
            </div>
        </div>
    `).join('');
}

// Find Alternative Medicines Function
function findAlternatives() {
    const searchTerm = document.getElementById('altSearch').value.toLowerCase().trim();
    const alternativesList = document.getElementById('alternativesList');
    
    if (!searchTerm) {
        alternativesList.innerHTML = '<div class="empty-state"><p>Veuillez entrer un nom de médicament</p></div>';
        return;
    }

    const alternatives = medicineEquivalents[searchTerm] || [];
    
    if (alternatives.length === 0) {
        alternativesList.innerHTML = '<div class="empty-state"><p>Aucune alternative trouvée pour ce médicament.</p></div>';
        return;
    }

    const alternativeMeds = medicinesDatabase.filter(med => 
        alternatives.some(alt => med.name.toLowerCase().includes(alt))
    );

    if (alternativeMeds.length === 0) {
        alternativesList.innerHTML = '<div class="empty-state"><p>Alternatives non disponibles actuellement.</p></div>';
        return;
    }

    alternativesList.innerHTML = alternativeMeds.map(med => `
        <div class="result-card">
            <div class="result-header">
                <div>
                    <div class="medicine-name">🔄 ${med.name}</div>
                    <div class="dosage">${med.dosage}</div>
                </div>
                <div class="price">${med.price} UM</div>
            </div>
            <div class="pharmacy-info">
                <div class="pharmacy-name">💊 ${med.pharmacy}</div>
                <div class="expiration-date">📅 Expiration: ${formatDate(med.expiration)}</div>
                <div class="expiration-date">📍 Région: ${med.region}</div>
                <p style="margin-top: 0.5rem; color: #1976D2; font-weight: 500;">✓ Alternative recommandée</p>
            </div>
        </div>
    `).join('');
}

// Set Rating Function
function setRating(stars) {
    selectedRating = stars;
    const starElements = document.querySelectorAll('.star-rating .star');
    starElements.forEach((star, index) => {
        if (index < stars) {
            star.classList.add('active');
        } else {
            star.classList.remove('active');
        }
    });
}

// Submit Rating Function
function submitRating() {
    const pharmacyName = document.getElementById('pharmacyName').value.trim();
    const ratingsList = document.getElementById('ratingsList');
    
    if (!pharmacyName) {
        alert('Veuillez entrer le nom de la pharmacie');
        return;
    }
    
    if (selectedRating === 0) {
        alert('Veuillez sélectionner une note (1-5 étoiles)');
        return;
    }

    const ratingHTML = `
        <div class="result-card">
            <div class="result-header">
                <div>
                    <div class="medicine-name">${pharmacyName}</div>
                </div>
                <div class="pharmacy-rating">${generateStars(selectedRating)}</div>
            </div>
            <div class="pharmacy-info">
                <p style="color: var(--primary-color); font-weight: 600;">✓ Évaluation enregistrée: ${selectedRating}/5</p>
            </div>
        </div>
    `;
    
    if (ratingsList.innerHTML.includes('empty-state')) {
        ratingsList.innerHTML = ratingHTML;
    } else {
        ratingsList.innerHTML = ratingHTML + ratingsList.innerHTML;
    }

    // Reset form
    document.getElementById('pharmacyName').value = '';
    selectedRating = 0;
    document.querySelectorAll('.star-rating .star').forEach(star => star.classList.remove('active'));
}

// Utility Functions
function formatDate(dateString) {
    const date = new Date(dateString);
    return date.toLocaleDateString('fr-FR', { year: 'numeric', month: 'long', day: 'numeric' });
}

function isExpirationSoon(expirationDate) {
    const today = new Date();
    const expDate = new Date(expirationDate);
    const thirtyDaysFromNow = new Date(today.getTime() + 30 * 24 * 60 * 60 * 1000);
    return expDate <= thirtyDaysFromNow && expDate >= today;
}

function generateStars(rating) {
    const fullStars = Math.floor(rating);
    const hasHalf = rating % 1 !== 0;
    let stars = '★'.repeat(fullStars);
    if (hasHalf) stars += '½';
    stars += '☆'.repeat(5 - Math.ceil(rating));
    return stars;
}

function scrollToSearch() {
    document.getElementById('search').scrollIntoView({ behavior: 'smooth' });
}

// Initialize on page load
document.addEventListener('DOMContentLoaded', function() {
    filterPharmacies();
});
